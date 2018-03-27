; Auto-generated. Do not edit!


(cl:in-package pca9685_msgs-msg)


;//! \htmlinclude PwmState.msg.html

(cl:defclass <PwmState> (roslisp-msg-protocol:ros-message)
  ((port_num
    :reader port_num
    :initarg :port_num
    :type cl:integer
    :initform 0)
   (on_value
    :reader on_value
    :initarg :on_value
    :type cl:integer
    :initform 0)
   (off_value
    :reader off_value
    :initarg :off_value
    :type cl:integer
    :initform 0))
)

(cl:defclass PwmState (<PwmState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PwmState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PwmState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pca9685_msgs-msg:<PwmState> is deprecated: use pca9685_msgs-msg:PwmState instead.")))

(cl:ensure-generic-function 'port_num-val :lambda-list '(m))
(cl:defmethod port_num-val ((m <PwmState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pca9685_msgs-msg:port_num-val is deprecated.  Use pca9685_msgs-msg:port_num instead.")
  (port_num m))

(cl:ensure-generic-function 'on_value-val :lambda-list '(m))
(cl:defmethod on_value-val ((m <PwmState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pca9685_msgs-msg:on_value-val is deprecated.  Use pca9685_msgs-msg:on_value instead.")
  (on_value m))

(cl:ensure-generic-function 'off_value-val :lambda-list '(m))
(cl:defmethod off_value-val ((m <PwmState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pca9685_msgs-msg:off_value-val is deprecated.  Use pca9685_msgs-msg:off_value instead.")
  (off_value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PwmState>) ostream)
  "Serializes a message object of type '<PwmState>"
  (cl:let* ((signed (cl:slot-value msg 'port_num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'on_value)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'off_value)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PwmState>) istream)
  "Deserializes a message object of type '<PwmState>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'port_num) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'on_value) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'off_value) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PwmState>)))
  "Returns string type for a message object of type '<PwmState>"
  "pca9685_msgs/PwmState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PwmState)))
  "Returns string type for a message object of type 'PwmState"
  "pca9685_msgs/PwmState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PwmState>)))
  "Returns md5sum for a message object of type '<PwmState>"
  "c450b9b5706be0ee075774bf4365c2f8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PwmState)))
  "Returns md5sum for a message object of type 'PwmState"
  "c450b9b5706be0ee075774bf4365c2f8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PwmState>)))
  "Returns full string definition for message of type '<PwmState>"
  (cl:format cl:nil "int32 port_num~%int32 on_value~%int32 off_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PwmState)))
  "Returns full string definition for message of type 'PwmState"
  (cl:format cl:nil "int32 port_num~%int32 on_value~%int32 off_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PwmState>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PwmState>))
  "Converts a ROS message object to a list"
  (cl:list 'PwmState
    (cl:cons ':port_num (port_num msg))
    (cl:cons ':on_value (on_value msg))
    (cl:cons ':off_value (off_value msg))
))
