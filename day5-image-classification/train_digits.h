#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/ml.hpp>
#include <QtGlobal>
#include "common.h"

namespace lcv
{
    namespace day5
    {
        auto const SZ = 20;
        int const affineFlags = cv::WARP_INVERSE_MAP | cv::INTER_LINEAR;
        cv::HOGDescriptor const hog{ cv::Size{ 20, 20 }, cv::Size{ 8, 8 }, cv::Size{ 4, 4 }, cv::Size{ 8, 8 }, 9, 1, -1.0, cv::HOGDescriptor::L2Hys, 0.2, false };

        cv::Mat deskew(cv::Mat& img)
        {
            cv::Moments m = moments(img);
            if(abs(m.mu02) < 1e-2)
                return img.clone();

            double const skew = m.mu11 / m.mu02;
            cv::Mat warpMat = (cv::Mat_<float>(2, 3) << 1, skew, -0.5 * SZ * skew, 0, 1, 0);
            cv::Mat imgOut = cv::Mat::zeros(img.rows, img.cols, img.type());
            cv::warpAffine(img, imgOut, warpMat, imgOut.size(), affineFlags);

            return imgOut;
        }

        void load_train_test_label(QString const &pathName, std::vector<cv::Mat> &trainCells, std::vector<cv::Mat> &testCells, std::vector<int> &trainLabels, std::vector<int> &testLabels)
        {
            cv::Mat img = imgFromQrc(pathName, cv::IMREAD_GRAYSCALE);
            int imgCount = 0;
            for(int i = 0; i < img.rows; i = i + SZ)
            {
                for(int j = 0; j < img.cols; j = j + SZ)
                {
                    cv::Mat digitImg = (img.colRange(j, j + SZ).rowRange(i, i + SZ)).clone();
                    if(j < static_cast<int>(0.9*img.cols))
                        trainCells.push_back(digitImg);
                    else
                        testCells.push_back(digitImg);
                    ++imgCount;
                }
            }

            std::cout << "Image Count : " << imgCount << std::endl;
            int digitClassNumber = 0;

            for(int z = 0; z < static_cast<int>(0.9 * imgCount); ++z)
            {
                if(z % 450 == 0 && z != 0)
                    digitClassNumber = digitClassNumber + 1;
                trainLabels.push_back(digitClassNumber);
            }
            digitClassNumber = 0;

            for(int z = 0; z < static_cast<int>(0.1 * imgCount); ++z)
            {
                if(z % 50 == 0 && z != 0)
                    digitClassNumber = digitClassNumber + 1;
                testLabels.push_back(digitClassNumber);
            }
        }

        void create_deskewed_train_test(std::vector<cv::Mat> &deskewedTrainCells, std::vector<cv::Mat> &deskewedTestCells, std::vector<cv::Mat> &trainCells, std::vector<cv::Mat> &testCells)
        {
            for(std::size_t i = 0; i < trainCells.size(); ++i)
            {
                cv::Mat deskewedImg = deskew(trainCells[i]);
                deskewedTrainCells.push_back(deskewedImg);
            }

            for(std::size_t i = 0; i < testCells.size(); ++i)
            {

                cv::Mat deskewedImg = deskew(testCells[i]);
                deskewedTestCells.push_back(deskewedImg);
            }
        }

        void create_train_test_hog(std::vector<std::vector<float>> &trainHOG, std::vector<std::vector<float>> &testHOG, std::vector<cv::Mat> &deskewedtrainCells, std::vector<cv::Mat> &deskewedtestCells)
        {
            for(std::size_t y = 0; y < deskewedtrainCells.size(); ++y)
            {
                std::vector<float> descriptors;
                hog.compute(deskewedtrainCells[y], descriptors);
                trainHOG.push_back(descriptors);
            }

            for(std::size_t y = 0; y < deskewedtestCells.size(); ++y)
            {
                std::vector<float> descriptors;
                hog.compute(deskewedtestCells[y], descriptors);
                testHOG.push_back(descriptors);
            }
        }

        void convert_vector_to_matrix(std::vector<std::vector<float>> &trainHOG, std::vector<std::vector<float>> &testHOG, cv::Mat &trainMat, cv::Mat &testMat)
        {
            auto const descriptor_size = trainHOG[0].size();

            for(std::size_t i = 0;i < trainHOG.size(); ++i)
                for(std::size_t j = 0; j < descriptor_size; ++j)
                   trainMat.at<float>(static_cast<int>(i), static_cast<int>(j)) = trainHOG[i][j];

            for(std::size_t i = 0; i < testHOG.size(); ++i)
                for(std::size_t j = 0; j < descriptor_size; ++j)
                    testMat.at<float>(static_cast<int>(i), static_cast<int>(j)) = testHOG[i][j];
        }

        void get_svm_params(cv::ml::SVM *svm)
        {
            std::cout << "Kernel type     : " << svm->getKernelType() << std::endl;
            std::cout << "Type            : " << svm->getType() << std::endl;
            std::cout << "C               : " << svm->getC() << std::endl;
            std::cout << "Degree          : " << svm->getDegree() << std::endl;
            std::cout << "Nu              : " << svm->getNu() << std::endl;
            std::cout << "Gamma           : " << svm->getGamma() << std::endl;
        }

        cv::Ptr<cv::ml::SVM> svmInit(double C, double gamma)
        {
            cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
            svm->setGamma(gamma);
            svm->setC(C);
            svm->setKernel(cv::ml::SVM::RBF);
            svm->setType(cv::ml::SVM::C_SVC);
            return svm;
        }

        void svm_train(cv::Ptr<cv::ml::SVM> svm, cv::Mat &trainMat, std::vector<int> &trainLabels)
        {
            cv::Ptr<cv::ml::TrainData> td = cv::ml::TrainData::create(trainMat, cv::ml::ROW_SAMPLE, trainLabels);
            svm->train(td);
            svm->save("results/eyeGlassClassifierModel.yml");
        }

        void svm_predict(cv::Ptr<cv::ml::SVM> svm, cv::Mat &testResponse, cv::Mat &testMat )
        {
            svm->predict(testMat, testResponse);
        }

        void svm_evaluate(cv::Mat &testResponse, float &count, float &accuracy, std::vector<int> &testLabels)
        {
            for(int i = 0; i < testResponse.rows; ++i)
            {
                if(qFuzzyCompare(testResponse.at<float>(i, 0), testLabels[static_cast<std::size_t>(i)]))
                    count = count + 1;
            }
            accuracy = (count / testResponse.rows) * 100;
        }

        void train_digits()
        {
            std::vector<cv::Mat> trainCells;
            std::vector<cv::Mat> testCells;
            std::vector<int> trainLabels;
            std::vector<int> testLabels;
            load_train_test_label(QStringLiteral(":/res/digits.png"), trainCells, testCells, trainLabels, testLabels);
            std::vector<cv::Mat> deskewedTrainCells;
            std::vector<cv::Mat> deskewedTestCells;
            create_deskewed_train_test(deskewedTrainCells, deskewedTestCells, trainCells, testCells);
            std::vector<std::vector<float>> trainHOG;
            std::vector<std::vector<float>> testHOG;
            create_train_test_hog(trainHOG, testHOG, deskewedTrainCells, deskewedTestCells);
            auto const descriptor_size = trainHOG[0].size();
            std::cout << "Descriptor Size : " << descriptor_size << std::endl;
            cv::Mat trainMat{ static_cast<int>(trainHOG.size()), static_cast<int>(descriptor_size), CV_32FC1 };
            cv::Mat testMat{ static_cast<int>(testHOG.size()), static_cast<int>(descriptor_size), CV_32FC1 };

            convert_vector_to_matrix(trainHOG, testHOG, trainMat, testMat);
            double const C = 12.5;
            double const gamma = 0.5;

            cv::Mat testResponse;
            cv::Ptr<cv::ml::SVM> model = svmInit(C, gamma);

            svm_train(model, trainMat, trainLabels);
            svm_predict(model, testResponse, testMat);

            float count = 0;
            float accuracy = 0 ;
            get_svm_params(model);
            svm_evaluate(testResponse, count, accuracy, testLabels);

            std::cout << "the accuracy is :" << accuracy << std::endl;
        }
    }
}
