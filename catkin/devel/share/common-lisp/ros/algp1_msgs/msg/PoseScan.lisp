; Auto-generated. Do not edit!


(cl:in-package algp1_msgs-msg)


;//! \htmlinclude PoseScan.msg.html

(cl:defclass <PoseScan> (roslisp-msg-protocol:ros-message)
  ((pose2d
    :reader pose2d
    :initarg :pose2d
    :type geometry_msgs-msg:Pose2D
    :initform (cl:make-instance 'geometry_msgs-msg:Pose2D))
   (ranges
    :reader ranges
    :initarg :ranges
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass PoseScan (<PoseScan>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PoseScan>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PoseScan)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name algp1_msgs-msg:<PoseScan> is deprecated: use algp1_msgs-msg:PoseScan instead.")))

(cl:ensure-generic-function 'pose2d-val :lambda-list '(m))
(cl:defmethod pose2d-val ((m <PoseScan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader algp1_msgs-msg:pose2d-val is deprecated.  Use algp1_msgs-msg:pose2d instead.")
  (pose2d m))

(cl:ensure-generic-function 'ranges-val :lambda-list '(m))
(cl:defmethod ranges-val ((m <PoseScan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader algp1_msgs-msg:ranges-val is deprecated.  Use algp1_msgs-msg:ranges instead.")
  (ranges m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PoseScan>) ostream)
  "Serializes a message object of type '<PoseScan>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose2d) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'ranges))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'ranges))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PoseScan>) istream)
  "Deserializes a message object of type '<PoseScan>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose2d) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'ranges) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'ranges)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PoseScan>)))
  "Returns string type for a message object of type '<PoseScan>"
  "algp1_msgs/PoseScan")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PoseScan)))
  "Returns string type for a message object of type 'PoseScan"
  "algp1_msgs/PoseScan")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PoseScan>)))
  "Returns md5sum for a message object of type '<PoseScan>"
  "d21cd8109f563aaf94a7906c0bc87f7a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PoseScan)))
  "Returns md5sum for a message object of type 'PoseScan"
  "d21cd8109f563aaf94a7906c0bc87f7a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PoseScan>)))
  "Returns full string definition for message of type '<PoseScan>"
  (cl:format cl:nil "# Pose for x, y, theta~%geometry_msgs/Pose2D pose2d~%~%# Array of float32s for ranges (is a vector)~%float32[] ranges~%================================================================================~%MSG: geometry_msgs/Pose2D~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PoseScan)))
  "Returns full string definition for message of type 'PoseScan"
  (cl:format cl:nil "# Pose for x, y, theta~%geometry_msgs/Pose2D pose2d~%~%# Array of float32s for ranges (is a vector)~%float32[] ranges~%================================================================================~%MSG: geometry_msgs/Pose2D~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PoseScan>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose2d))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ranges) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PoseScan>))
  "Converts a ROS message object to a list"
  (cl:list 'PoseScan
    (cl:cons ':pose2d (pose2d msg))
    (cl:cons ':ranges (ranges msg))
))
