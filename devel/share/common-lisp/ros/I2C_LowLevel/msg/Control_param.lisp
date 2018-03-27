; Auto-generated. Do not edit!


(cl:in-package I2C_LowLevel-msg)


;//! \htmlinclude Control_param.msg.html

(cl:defclass <Control_param> (roslisp-msg-protocol:ros-message)
  ((steering_angle
    :reader steering_angle
    :initarg :steering_angle
    :type cl:float
    :initform 0.0)
   (throttle
    :reader throttle
    :initarg :throttle
    :type cl:integer
    :initform 0))
)

(cl:defclass Control_param (<Control_param>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Control_param>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Control_param)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name I2C_LowLevel-msg:<Control_param> is deprecated: use I2C_LowLevel-msg:Control_param instead.")))

(cl:ensure-generic-function 'steering_angle-val :lambda-list '(m))
(cl:defmethod steering_angle-val ((m <Control_param>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader I2C_LowLevel-msg:steering_angle-val is deprecated.  Use I2C_LowLevel-msg:steering_angle instead.")
  (steering_angle m))

(cl:ensure-generic-function 'throttle-val :lambda-list '(m))
(cl:defmethod throttle-val ((m <Control_param>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader I2C_LowLevel-msg:throttle-val is deprecated.  Use I2C_LowLevel-msg:throttle instead.")
  (throttle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Control_param>) ostream)
  "Serializes a message object of type '<Control_param>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steering_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'throttle)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'throttle)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'throttle)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'throttle)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Control_param>) istream)
  "Deserializes a message object of type '<Control_param>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'throttle)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'throttle)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'throttle)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'throttle)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Control_param>)))
  "Returns string type for a message object of type '<Control_param>"
  "I2C_LowLevel/Control_param")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Control_param)))
  "Returns string type for a message object of type 'Control_param"
  "I2C_LowLevel/Control_param")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Control_param>)))
  "Returns md5sum for a message object of type '<Control_param>"
  "d5b20e2f8b2fbd2c6b6eaefb88e997d7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Control_param)))
  "Returns md5sum for a message object of type 'Control_param"
  "d5b20e2f8b2fbd2c6b6eaefb88e997d7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Control_param>)))
  "Returns full string definition for message of type '<Control_param>"
  (cl:format cl:nil "float32 steering_angle~%uint32 throttle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Control_param)))
  "Returns full string definition for message of type 'Control_param"
  (cl:format cl:nil "float32 steering_angle~%uint32 throttle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Control_param>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Control_param>))
  "Converts a ROS message object to a list"
  (cl:list 'Control_param
    (cl:cons ':steering_angle (steering_angle msg))
    (cl:cons ':throttle (throttle msg))
))
