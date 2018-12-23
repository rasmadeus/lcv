#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv2/opencv.hpp>
#include "common.h"

namespace lcv
{
    namespace day7
    {
        void write_landmarks_to_file(dlib::full_object_detection &landmarks, std::string const &filename)
        {
            std::ofstream ofs;
            ofs.open(filename);

            for (unsigned long i = 0; i < landmarks.num_parts(); i++)
                ofs << landmarks.part(i).x() << " " << landmarks.part(i).y() << std::endl;

            ofs.close();
        }

        void draw_landmarks(cv::Mat &im, dlib::full_object_detection landmarks)
        {
            for(unsigned long i = 0; i < landmarks.num_parts(); i++)
            {
                auto const px = static_cast<int>(landmarks.part(i).x());
                auto const py = static_cast<int>(landmarks.part(i).y());

                char landmark_index[3];
                sprintf(landmark_index, "%d", static_cast<int>(i)+1);

                cv::circle(im, cv::Point{ px, py }, 1, cv::Scalar{ 0, 0, 255 }, 2, cv::LINE_AA);
                cv::putText(im, landmark_index, cv::Point{ px, py }, cv::FONT_HERSHEY_SIMPLEX, 0.3, cv::Scalar{ 255, 0, 0 }, 1);
            }
        }

        void facial_landmark_detector()
        {
            dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
            dlib::shape_predictor landmarkDetector;
            dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> landmarkDetector;

            std::string imageFilename{ "girl.jpg" };
            cv::Mat im = cv::imread(imageFilename);

            std::string landmarksBasename{ "output_cpp" };
            dlib::cv_image<dlib::bgr_pixel> dlibIm{ im };

            std::vector<dlib::rectangle> faceRects = faceDetector(dlibIm);
            std::cout << "Number of faces detected: " << faceRects.size() << std::endl;

            std::vector<dlib::full_object_detection> landmarksAll;

            for (unsigned int i = 0; i < faceRects.size(); i++)
            {
                dlib::full_object_detection landmarks = landmarkDetector(dlibIm, faceRects[i]);
                if (i == 0)
                    std::cout << "Number of landmarks : " << landmarks.num_parts() << std::endl;

                landmarksAll.push_back(landmarks);
                draw_landmarks(im, landmarks);

                std::stringstream landmarksFilename;
                landmarksFilename << landmarksBasename <<  "_"  << i << ".txt";
                std::cout << "Saving landmarks to " << landmarksFilename.str() << std::endl;
                write_landmarks_to_file(landmarks, landmarksFilename.str());
            }

            std::string outputFilename{ "result_cpp_Landmarks.jpg" };
            std::cout << "Saving output image to " << outputFilename << std::endl;
            cv::imwrite(outputFilename, im);

            cv::imshow("Facial Landmark Detector", im);
            cv::waitKey(0);
        }
    }
}
