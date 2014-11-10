
(cl:in-package :asdf)

(defsystem "algp1_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "Pose2DWithCovariance" :depends-on ("_package_Pose2DWithCovariance"))
    (:file "_package_Pose2DWithCovariance" :depends-on ("_package"))
  ))