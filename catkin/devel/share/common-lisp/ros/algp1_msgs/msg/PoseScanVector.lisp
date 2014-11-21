; Auto-generated. Do not edit!


(cl:in-package algp1_msgs-msg)


;//! \htmlinclude PoseScanVector.msg.html

(cl:defclass <PoseScanVector> (roslisp-msg-protocol:ros-message)
  ((scans
    :reader scans
    :initarg :scans
    :type (cl:vector algp1_msgs-msg:PoseScan)
   :initform (cl:make-array 0 :element-type 'algp1_msgs-msg:PoseScan :initial-element (cl:make-instance 'algp1_msgs-msg:PoseScan))))
)

(cl:defclass PoseScanVector (<PoseScanVector>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PoseScanVector>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PoseScanVector)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name algp1_msgs-msg:<PoseScanVector> is deprecated: use algp1_msgs-msg:PoseScanVector instead.")))

(cl:ensure-generic-function 'scans-val :lambda-list '(m))
(cl:defmethod scans-val ((m <PoseScanVector>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader algp1_msgs-msg:scans-val is deprecated.  Use algp1_msgs-msg:scans instead.")
  (scans m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PoseScanVector>) ostream)
  "Serializes a message object of type '<PoseScanVector>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'scans))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'scans))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PoseScanVector>) istream)
  "Deserializes a message object of type '<PoseScanVector>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'scans) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'scans)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'algp1_msgs-msg:PoseScan))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PoseScanVector>)))
  "Returns string type for a message object of type '<PoseScanVector>"
  "algp1_msgs/PoseScanVector")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PoseScanVector)))
  "Returns string type for a message object of type 'PoseScanVector"
  "algp1_msgs/PoseScanVector")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PoseScanVector>)))
  "Returns md5sum for a message object of type '<PoseScanVector>"
  "630b2b0ca1c5d59f453e5c5806f5c1ac")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PoseScanVector)))
  "Returns md5sum for a message object of type 'PoseScanVector"
  "630b2b0ca1c5d59f453e5c5806f5c1ac")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PoseScanVector>)))
  "Returns full string definition for message of type '<PoseScanVector>"
  (cl:format cl:nil "algp1_msgs/PoseScan[] scans~%================================================================================~%MSG: algp1_msgs/PoseScan~%# Pose for x, y, theta~%geometry_msgs/Pose2D pose2d~%~%# Array of float32s for ranges (is a vector)~%float32[] ranges~%================================================================================~%MSG: geometry_msgs/Pose2D~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PoseScanVector)))
  "Returns full string definition for message of type 'PoseScanVector"
  (cl:format cl:nil "algp1_msgs/PoseScan[] scans~%================================================================================~%MSG: algp1_msgs/PoseScan~%# Pose for x, y, theta~%geometry_msgs/Pose2D pose2d~%~%# Array of float32s for ranges (is a vector)~%float32[] ranges~%================================================================================~%MSG: geometry_msgs/Pose2D~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PoseScanVector>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'scans) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PoseScanVector>))
  "Converts a ROS message object to a list"
  (cl:list 'PoseScanVector
    (cl:cons ':scans (scans msg))
))
