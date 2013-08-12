/* Auto-generated by genmsg_cpp for file /home/sisir/irobot-hand/Software/2013_08_07_full/handle/handle_msgs/msg/HandleCollisions.msg */
#ifndef HANDLE_MSGS_MESSAGE_HANDLECOLLISIONS_H
#define HANDLE_MSGS_MESSAGE_HANDLECOLLISIONS_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "std_msgs/Header.h"
#include "handle_msgs/Collision.h"

namespace handle_msgs
{
template <class ContainerAllocator>
struct HandleCollisions_ {
  typedef HandleCollisions_<ContainerAllocator> Type;

  HandleCollisions_()
  : header()
  , collisions()
  {
  }

  HandleCollisions_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , collisions(_alloc)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef std::vector< ::handle_msgs::Collision_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::handle_msgs::Collision_<ContainerAllocator> >::other >  _collisions_type;
  std::vector< ::handle_msgs::Collision_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::handle_msgs::Collision_<ContainerAllocator> >::other >  collisions;


  typedef boost::shared_ptr< ::handle_msgs::HandleCollisions_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::handle_msgs::HandleCollisions_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct HandleCollisions
typedef  ::handle_msgs::HandleCollisions_<std::allocator<void> > HandleCollisions;

typedef boost::shared_ptr< ::handle_msgs::HandleCollisions> HandleCollisionsPtr;
typedef boost::shared_ptr< ::handle_msgs::HandleCollisions const> HandleCollisionsConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::handle_msgs::HandleCollisions_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::handle_msgs::HandleCollisions_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace handle_msgs

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::handle_msgs::HandleCollisions_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::handle_msgs::HandleCollisions_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::handle_msgs::HandleCollisions_<ContainerAllocator> > {
  static const char* value() 
  {
    return "4beb2df6b938c5819449df17bcfbc49b";
  }

  static const char* value(const  ::handle_msgs::HandleCollisions_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x4beb2df6b938c581ULL;
  static const uint64_t static_value2 = 0x9449df17bcfbc49bULL;
};

template<class ContainerAllocator>
struct DataType< ::handle_msgs::HandleCollisions_<ContainerAllocator> > {
  static const char* value() 
  {
    return "handle_msgs/HandleCollisions";
  }

  static const char* value(const  ::handle_msgs::HandleCollisions_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::handle_msgs::HandleCollisions_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# This is sensors of the HANDLE hand after calibration and data manipulation\n\
# published from the package sensors, by the sensors_publisher\n\
\n\
# not all the sensors were included, but only the one which were addressed at the moment\n\
\n\
# Currently only used for time stamp.  \n\
Header header\n\
\n\
Collision[] collisions\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: handle_msgs/Collision\n\
# This is basic collision message\n\
# it is used in HandleCollisions to build an array\n\
\n\
string frame_id\n\
# finger[0]/proximal_link\n\
# finger[0]/distal_link\n\
# finger[1]/proximal_link\n\
# finger[1]/distal_link\n\
# finger[2]/proximal_link\n\
# finger[2]/distal_link\n\
# base_link\n\
\n\
int32 sensor_id\n\
# index of sensor\n\
\n\
float32 intensity\n\
\n\
# location of sensor on the surface of the finger in the link frame\n\
float32 x\n\
float32 y\n\
float32 z\n\
\n\
";
  }

  static const char* value(const  ::handle_msgs::HandleCollisions_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::handle_msgs::HandleCollisions_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::handle_msgs::HandleCollisions_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::handle_msgs::HandleCollisions_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.collisions);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct HandleCollisions_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::handle_msgs::HandleCollisions_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::handle_msgs::HandleCollisions_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "collisions[]" << std::endl;
    for (size_t i = 0; i < v.collisions.size(); ++i)
    {
      s << indent << "  collisions[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::handle_msgs::Collision_<ContainerAllocator> >::stream(s, indent + "    ", v.collisions[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // HANDLE_MSGS_MESSAGE_HANDLECOLLISIONS_H

