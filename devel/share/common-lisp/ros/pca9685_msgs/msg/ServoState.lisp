; Auto-generated. Do not edit!


(cl:in-package pca9685_msgs-msg)


;//! \htmlinclude ServoState.msg.html

(cl:defclass <ServoState> (roslisp-msg-protocol:ros-message)
  ((port_num
    :reader port_num
    :initarg :port_num
    :type cl:integer
    :initform 0)
   (servo_type
    :reader servo_type
    :initarg :servo_type
    :type cl:integer
    :initform 0)
   (servo_rot
    :reader servo_rot
    :initarg :servo_rot
    :type cl:float
    :initform 0.0))
)

(cl:defclass ServoState (<ServoState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ServoState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ServoState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name pca9685_msgs-msg:<ServoState> is deprecated: use pca9685_msgs-msg:ServoState instead.")))

(cl:ensure-generic-function 'port_num-val :lambda-list '(m))
(cl:defmethod port_num-val ((m <ServoState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pca9685_msgs-msg:port_num-val is deprecated.  Use pca9685_msgs-msg:port_num instead.")
  (port_num m))

(cl:ensure-generic-function 'servo_type-val :lambda-list '(m))
(cl:defmethod servo_type-val ((m <ServoState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pca9685_msgs-msg:servo_type-val is deprecated.  Use pca9685_msgs-msg:servo_type instead.")
  (servo_type m))

(cl:ensure-generic-function 'servo_rot-val :lambda-list '(m))
(cl:defmethod servo_rot-val ((m <ServoState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader pca9685_msgs-msg:servo_rot-val is deprecated.  Use pca9685_msgs-msg:servo_rot instead.")
  (servo_rot m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<ServoState>)))
    "Constants for message type '<ServoState>"
  '((:STOP . 0)
    (:D009A . 1)
    (:D150A . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'ServoState)))
    "Constants for message type 'ServoState"
  '((:STOP . 0)
    (:D009A . 1)
    (:D150A . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ServoState>) ostream)
  "Serializes a message object of type '<ServoState>"
  (cl:let* ((signed (cl:slot-value msg 'port_num)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'servo_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'servo_rot))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ServoState>) istream)
  "Deserializes a message object of type '<ServoState>"
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
      (cl:setf (cl:slot-value msg 'servo_type) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'servo_rot) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ServoState>)))
  "Returns string type for a message object of type '<ServoState>"
  "pca9685_msgs/ServoState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ServoState)))
  "Returns string type for a message object of type 'ServoState"
  "pca9685_msgs/ServoState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ServoState>)))
  "Returns md5sum for a message object of type '<ServoState>"
  "844ba134507d19332dd881679bd50ba2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ServoState)))
  "Returns md5sum for a message object of type 'ServoState"
  "844ba134507d19332dd881679bd50ba2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ServoState>)))
  "Returns full string definition for message of type '<ServoState>"
  (cl:format cl:nil "int32 port_num~%int32 servo_type~%float32 servo_rot~%~%int32 STOP  = 0~%int32 D009A = 1~%int32 D150A = 2~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ServoState)))
  "Returns full string definition for message of type 'ServoState"
  (cl:format cl:nil "int32 port_num~%int32 servo_type~%float32 servo_rot~%~%int32 STOP  = 0~%int32 D009A = 1~%int32 D150A = 2~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ServoState>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ServoState>))
  "Converts a ROS message object to a list"
  (cl:list 'ServoState
    (cl:cons ':port_num (port_num msg))
    (cl:cons ':servo_type (servo_type msg))
    (cl:cons ':servo_rot (servo_rot msg))
))
