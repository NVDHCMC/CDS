// Generated by gencpp from file i2cpwm_board/IntValueRequest.msg
// DO NOT EDIT!


#ifndef I2CPWM_BOARD_MESSAGE_INTVALUEREQUEST_H
#define I2CPWM_BOARD_MESSAGE_INTVALUEREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace i2cpwm_board
{
template <class ContainerAllocator>
struct IntValueRequest_
{
  typedef IntValueRequest_<ContainerAllocator> Type;

  IntValueRequest_()
    : value(0)  {
    }
  IntValueRequest_(const ContainerAllocator& _alloc)
    : value(0)  {
  (void)_alloc;
    }



   typedef int16_t _value_type;
  _value_type value;




  typedef boost::shared_ptr< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> const> ConstPtr;

}; // struct IntValueRequest_

typedef ::i2cpwm_board::IntValueRequest_<std::allocator<void> > IntValueRequest;

typedef boost::shared_ptr< ::i2cpwm_board::IntValueRequest > IntValueRequestPtr;
typedef boost::shared_ptr< ::i2cpwm_board::IntValueRequest const> IntValueRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::i2cpwm_board::IntValueRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace i2cpwm_board

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'i2cpwm_board': ['/home/ubuntu/catkin_ws/src/ros-i2cpwmboard-master/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "55daaea9ec64e37c8a6144d42a7265e2";
  }

  static const char* value(const ::i2cpwm_board::IntValueRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x55daaea9ec64e37cULL;
  static const uint64_t static_value2 = 0x8a6144d42a7265e2ULL;
};

template<class ContainerAllocator>
struct DataType< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "i2cpwm_board/IntValueRequest";
  }

  static const char* value(const ::i2cpwm_board::IntValueRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
\n\
\n\
int16 value\n\
";
  }

  static const char* value(const ::i2cpwm_board::IntValueRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.value);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct IntValueRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::i2cpwm_board::IntValueRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::i2cpwm_board::IntValueRequest_<ContainerAllocator>& v)
  {
    s << indent << "value: ";
    Printer<int16_t>::stream(s, indent + "  ", v.value);
  }
};

} // namespace message_operations
} // namespace ros

#endif // I2CPWM_BOARD_MESSAGE_INTVALUEREQUEST_H
