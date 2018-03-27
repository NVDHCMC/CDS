
(cl:in-package :asdf)

(defsystem "I2C_LowLevel-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Control_param" :depends-on ("_package_Control_param"))
    (:file "_package_Control_param" :depends-on ("_package"))
  ))