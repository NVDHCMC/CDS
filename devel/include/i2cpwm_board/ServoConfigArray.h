// Generated by gencpp from file i2cpwm_board/ServoConfigArray.msg
// DO NOT EDIT!


#ifndef I2CPWM_BOARD_MESSAGE_SERVOCONFIGARRAY_H
#define I2CPWM_BOARD_MESSAGE_SERVOCONFIGARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <i2cpwm_board/ServoConfig.h>

namespace i2cpwm_board
{
template <class ContainerAllocator>
struct ServoConfigArray_
{
  typedef ServoConfigArray_<ContainerAllocator> Type;

  ServoConfigArray_()
    : servos()  {
    }
  ServoConfigArray_(const ContainerAllocator& _alloc)
    : servos(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::i2cpwm_board::ServoConfig_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::i2cpwm_board::ServoConfig_<ContainerAllocator> >::other >  _servos_type;
  _servos_type servos;




  typedef boost::shared_ptr< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> const> ConstPtr;

}; // struct ServoConfigArray_

typedef ::i2cpwm_board::ServoConfigArray_<std::allocator<void> > ServoConfigArray;

typedef boost::shared_ptr< ::i2cpwm_board::ServoConfigArray > ServoConfigArrayPtr;
typedef boost::shared_ptr< ::i2cpwm_board::ServoConfigArray const> ServoConfigArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace i2cpwm_board

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'i2cpwm_board': ['/home/ubuntu/catkin_ws/src/ros-i2cpwmboard-master/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8f9c43713b493f265aec1e926dd292b8";
  }

  static const char* value(const ::i2cpwm_board::ServoConfigArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8f9c43713b493f26ULL;
  static const uint64_t static_value2 = 0x5aec1e926dd292b8ULL;
};

template<class ContainerAllocator>
struct DataType< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "i2cpwm_board/ServoConfigArray";
  }

  static const char* value(const ::i2cpwm_board::ServoConfigArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# the ServoConfigArray message is used to handle multiple assignments\n\
# of config data to servos. the data is needed to normalize servos to\n\
# common values to isolate variations from the rest of the user's\n\
# robot motion code. \n\
\n\
ServoConfig[] servos\n\
\n\
================================================================================\n\
MSG: i2cpwm_board/ServoConfig\n\
# the ServoConfig message is used to assign specific configuration\n\
# data to a servo. the data is needed to normalize servos to\n\
# common values to isolate variations from the rest of the user's\n\
# robot motion code. \n\
\n\
int16 servo\n\
int16 center\n\
int16 range\n\
int16 direction\n\
";
  }

  static const char* value(const ::i2cpwm_board::ServoConfigArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.servos);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ServoConfigArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::i2cpwm_board::ServoConfigArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::i2cpwm_board::ServoConfigArray_<ContainerAllocator>& v)
  {
    s << indent << "servos[]" << std::endl;
    for (size_t i = 0; i < v.servos.size(); ++i)
    {
      s << indent << "  servos[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::i2cpwm_board::ServoConfig_<ContainerAllocator> >::stream(s, indent + "    ", v.servos[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // I2CPWM_BOARD_MESSAGE_SERVOCONFIGARRAY_H
