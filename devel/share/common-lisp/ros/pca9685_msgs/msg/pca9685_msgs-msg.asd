
(cl:in-package :asdf)

(defsystem "pca9685_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "ServoState" :depends-on ("_package_ServoState"))
    (:file "_package_ServoState" :depends-on ("_package"))
    (:file "PwmState" :depends-on ("_package_PwmState"))
    (:file "_package_PwmState" :depends-on ("_package"))
  ))