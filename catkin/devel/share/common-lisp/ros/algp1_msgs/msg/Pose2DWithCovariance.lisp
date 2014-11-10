; Auto-generated. Do not edit!


(cl:in-package algp1_msgs-msg)


;//! \htmlinclude Pose2DWithCovariance.msg.html

(cl:defclass <Pose2DWithCovariance> (roslisp-msg-protocol:ros-message)
  ((pose2d
    :reader pose2d
    :initarg :pose2d
    :type geometry_msgs-msg:Pose2D
    :initform (cl:make-instance 'geometry_msgs-msg:Pose2D))
   (covariance
    :reader covariance
    :initarg :covariance
    :type (cl:vector cl:float)
   :initform (cl:make-array 9 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass Pose2DWithCovariance (<Pose2DWithCovariance>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Pose2DWithCovariance>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Pose2DWithCovariance)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name algp1_msgs-msg:<Pose2DWithCovariance> is deprecated: use algp1_msgs-msg:Pose2DWithCovariance instead.")))

(cl:ensure-generic-function 'pose2d-val :lambda-list '(m))
(cl:defmethod pose2d-val ((m <Pose2DWithCovariance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader algp1_msgs-msg:pose2d-val is deprecated.  Use algp1_msgs-msg:pose2d instead.")
  (pose2d m))

(cl:ensure-generic-function 'covariance-val :lambda-list '(m))
(cl:defmethod covariance-val ((m <Pose2DWithCovariance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader algp1_msgs-msg:covariance-val is deprecated.  Use algp1_msgs-msg:covariance instead.")
  (covariance m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Pose2DWithCovariance>) ostream)
  "Serializes a message object of type '<Pose2DWithCovariance>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose2d) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'covariance))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Pose2DWithCovariance>) istream)
  "Deserializes a message object of type '<Pose2DWithCovariance>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose2d) istream)
  (cl:setf (cl:slot-value msg 'covariance) (cl:make-array 9))
  (cl:let ((vals (cl:slot-value msg 'covariance)))
    (cl:dotimes (i 9)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Pose2DWithCovariance>)))
  "Returns string type for a message object of type '<Pose2DWithCovariance>"
  "algp1_msgs/Pose2DWithCovariance")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Pose2DWithCovariance)))
  "Returns string type for a message object of type 'Pose2DWithCovariance"
  "algp1_msgs/Pose2DWithCovariance")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Pose2DWithCovariance>)))
  "Returns md5sum for a message object of type '<Pose2DWithCovariance>"
  "ec0050e0d8397013a38802a448163fa4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Pose2DWithCovariance)))
  "Returns md5sum for a message object of type 'Pose2DWithCovariance"
  "ec0050e0d8397013a38802a448163fa4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Pose2DWithCovariance>)))
  "Returns full string definition for message of type '<Pose2DWithCovariance>"
  (cl:format cl:nil "# 2D pose for STDR sim~%geometry_msgs/Pose2D pose2d~%~%# Row-major representation of the 3x3 covariance matrix~%# (x, y, theta)~%float64[9] covariance~%================================================================================~%MSG: geometry_msgs/Pose2D~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Pose2DWithCovariance)))
  "Returns full string definition for message of type 'Pose2DWithCovariance"
  (cl:format cl:nil "# 2D pose for STDR sim~%geometry_msgs/Pose2D pose2d~%~%# Row-major representation of the 3x3 covariance matrix~%# (x, y, theta)~%float64[9] covariance~%================================================================================~%MSG: geometry_msgs/Pose2D~%# This expresses a position and orientation on a 2D manifold.~%~%float64 x~%float64 y~%float64 theta~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Pose2DWithCovariance>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose2d))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'covariance) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Pose2DWithCovariance>))
  "Converts a ROS message object to a list"
  (cl:list 'Pose2DWithCovariance
    (cl:cons ':pose2d (pose2d msg))
    (cl:cons ':covariance (covariance msg))
))
