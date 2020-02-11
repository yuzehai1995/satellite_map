//
// Created by fish on 19-5-16.
//
#ifndef INC_3DRECONSTRUCTION_CONFIG_H
#define INC_3DRECONSTRUCTION_CONFIG_H

#include <iostream>
#include <memory>

#include <opencv2/core/core.hpp>

using namespace std;
using cv::Mat;

class Config {

private:
    static std::shared_ptr<Config> config_;
    cv::FileStorage file_;

    Config () {} // private constructor makes a singleton
public:
    ~Config();  // close the file when deconstructing

    // set a new config file
    static void setParameterFile( const std::string& filename );

    // access the parameter values
    template< typename T >
    static T get( const std::string& key )
    {
        return T( Config::config_->file_[key] );
    }

};


#endif //INC_3DRECONSTRUCTION_CONFIG_H
