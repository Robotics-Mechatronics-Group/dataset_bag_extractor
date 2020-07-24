#pragma once

#include "bag_extractor/Utils.hpp"

// ROS
#include <ros/ros.h>

// Bag reading and processing
#include <rosbag/bag.h>
#include <rosbag/view.h>

// PC specific includes
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>

// STD
#include <string>

namespace bag_extractor
{

/*!
*  Main class for the node to handle the ROS interfacing.
*/
class PC2BIN
{

public:
    /*!
     * Constructor.
     * @param nodeHandle the ROS node handle.
     */
    PC2BIN(ros::NodeHandle &nodeHandle);

    /*!
     * Destructor;
     */
    virtual ~PC2BIN();

    /*!
     * Extract all data.
     */
    void extract();

private:
    /*!
     * Reads and verifies the ROS parameters.
     * @return true if succesful.
     */
    bool readParameters_();

    /*!
     * Set the time queries if the time limits have been set.
     * @param start the starting ros time for the query.
     * @param end the end ros time for the query.
     */
    void setTimeFilters_(ros::Time &start, ros::Time &end);

    /*!
     * ROS topic callback method.
     * @param message the received message.
     */
    void pcMsgProcess_(const sensor_msgs::PointCloud2ConstPtr &msg);

    //! ROS node handle.
    ros::NodeHandle &nodeHandle_;

    //! Counter for the number of files
    int counter_;

    //! Folder name for the saved point clouds
    std::string folder_;

    //! File to save the Velodyne data
    std::ofstream out_;

    //! Velodyne topic name
    std::string topic_;

    //! Bag name
    std::string bagName_;

    //! Rosbag
    rosbag::Bag bag_;


    //! Start time for the bag query.
    double start_time_filter_;

    //! End time for the bag query.
    double end_time_filter_;

    //! Part of the folder name used for the file name (Specific use case).
    std::string device_;
    
    //! Extension of the file to save the data.
    const std::string EXTENSION_ = ".bin";
};

} // namespace bag_extractor