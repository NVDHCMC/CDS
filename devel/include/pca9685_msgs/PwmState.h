// Generated by gencpp from file pca9685_msgs/PwmState.msg
// DO NOT EDIT!


#ifndef PCA9685_MSGS_MESSAGE_PWMSTATE_H
#define PCA9685_MSGS_MESSAGE_PWMSTATE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace pca9685_msgs
{
template <class ContainerAllocator>
struct PwmState_
{
  typedef PwmState_<ContainerAllocator> Type;

  PwmState_()
    : port_num(0)
    , on_value(0)
    , off_value(0)  {
    }
  PwmState_(const ContainerAllocator& _alloc)
    : port_num(0)
    , on_value(0)
    , off_value(0)  {
  (void)_alloc;
    }



   typedef int32_t _port_num_type;
  _port_num_type port_num;

   typedef int32_t _on_value_type;
  _on_value_type on_value;

   typedef int32_t _off_value_type;
  _off_value_type off_value;




  typedef boost::shared_ptr< ::pca9685_msgs::PwmState_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::pca9685_msgs::PwmState_<ContainerAllocator> const> ConstPtr;

}; // struct PwmState_

typedef ::pca9685_msgs::PwmState_<std::allocator<void> > PwmState;

typedef boost::shared_ptr< ::pca9685_msgs::PwmState > PwmStatePtr;
typedef boost::shared_ptr< ::pca9685_msgs::PwmState const> PwmStateConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::pca9685_msgs::PwmState_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::pca9685_msgs::PwmState_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace pca9685_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'pca9685_msgs': ['/home/ubuntu/catkin_ws/src/pca9685_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::pca9685_msgs::PwmState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::pca9685_msgs::PwmState_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::pca9685_msgs::PwmState_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::pca9685_msgs::PwmState_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pca9685_msgs::PwmState_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pca9685_msgs::PwmState_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::pca9685_msgs::PwmState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c450b9b5706be0ee075774bf4365c2f8";
  }

  static const char* value(const ::pca9685_msgs::PwmState_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc450b9b5706be0eeULL;
  static const uint64_t static_value2 = 0x075774bf4365c2f8ULL;
};

template<class ContainerAllocator>
struct DataType< ::pca9685_msgs::PwmState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "pca9685_msgs/PwmState";
  }

  static const char* value(const ::pca9685_msgs::PwmState_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::pca9685_msgs::PwmState_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 port_num\n\
int32 on_value\n\
int32 off_value\n\
";
  }

  static const char* value(const ::pca9685_msgs::PwmState_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::pca9685_msgs::PwmState_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.port_num);
      stream.next(m.on_value);
      stream.next(m.off_value);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PwmState_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::pca9685_msgs::PwmState_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::pca9685_msgs::PwmState_<ContainerAllocator>& v)
  {
    s << indent << "port_num: ";
    Printer<int32_t>::stream(s, indent + "  ", v.port_num);
    s << indent << "on_value: ";
    Printer<int32_t>::stream(s, indent + "  ", v.on_value);
    s << indent << "off_value: ";
    Printer<int32_t>::stream(s, indent + "  ", v.off_value);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PCA9685_MSGS_MESSAGE_PWMSTATE_H
