/* Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Auto-generated by genmsg_cpp from file /home/luc/ros_workspace/alg_robo_p1/catkin/src/algp1_msgs/msg/Pose2DWithCovariance.msg
 *
 */


#ifndef ALGP1_MSGS_MESSAGE_POSE2DWITHCOVARIANCE_H
#define ALGP1_MSGS_MESSAGE_POSE2DWITHCOVARIANCE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose2D.h>

namespace algp1_msgs
{
template <class ContainerAllocator>
struct Pose2DWithCovariance_
{
  typedef Pose2DWithCovariance_<ContainerAllocator> Type;

  Pose2DWithCovariance_()
    : pose2d()
    , covariance()  {
      covariance.assign(0.0);
  }
  Pose2DWithCovariance_(const ContainerAllocator& _alloc)
    : pose2d(_alloc)
    , covariance()  {
      covariance.assign(0.0);
  }



   typedef  ::geometry_msgs::Pose2D_<ContainerAllocator>  _pose2d_type;
  _pose2d_type pose2d;

   typedef boost::array<double, 9>  _covariance_type;
  _covariance_type covariance;




  typedef boost::shared_ptr< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;

}; // struct Pose2DWithCovariance_

typedef ::algp1_msgs::Pose2DWithCovariance_<std::allocator<void> > Pose2DWithCovariance;

typedef boost::shared_ptr< ::algp1_msgs::Pose2DWithCovariance > Pose2DWithCovariancePtr;
typedef boost::shared_ptr< ::algp1_msgs::Pose2DWithCovariance const> Pose2DWithCovarianceConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace algp1_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'nav_msgs': ['/opt/ros/hydro/share/nav_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/hydro/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/hydro/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/hydro/share/std_msgs/cmake/../msg'], 'algp1_msgs': ['/home/luc/ros_workspace/alg_robo_p1/catkin/src/algp1_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ec0050e0d8397013a38802a448163fa4";
  }

  static const char* value(const ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xec0050e0d8397013ULL;
  static const uint64_t static_value2 = 0xa38802a448163fa4ULL;
};

template<class ContainerAllocator>
struct DataType< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> >
{
  static const char* value()
  {
    return "algp1_msgs/Pose2DWithCovariance";
  }

  static const char* value(const ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# 2D pose for STDR sim\n\
geometry_msgs/Pose2D pose2d\n\
\n\
# Row-major representation of the 3x3 covariance matrix\n\
# (x, y, theta)\n\
float64[9] covariance\n\
================================================================================\n\
MSG: geometry_msgs/Pose2D\n\
# This expresses a position and orientation on a 2D manifold.\n\
\n\
float64 x\n\
float64 y\n\
float64 theta\n\
";
  }

  static const char* value(const ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.pose2d);
      stream.next(m.covariance);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct Pose2DWithCovariance_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::algp1_msgs::Pose2DWithCovariance_<ContainerAllocator>& v)
  {
    s << indent << "pose2d: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose2D_<ContainerAllocator> >::stream(s, indent + "  ", v.pose2d);
    s << indent << "covariance[]" << std::endl;
    for (size_t i = 0; i < v.covariance.size(); ++i)
    {
      s << indent << "  covariance[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.covariance[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ALGP1_MSGS_MESSAGE_POSE2DWITHCOVARIANCE_H
