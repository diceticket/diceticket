SetOutFileName("lane20")

link_libraries(opencv_core opencv_highgui opencv_imgproc opencv_calib3d)

add_executable(${output_filename} 
../crypto/hmac_sha256.cpp
../crypto/hmac_sha512.cpp
../crypto/ripemd160.cpp
../crypto/scrypt.cpp
../crypto/scrypt-sse2.cpp
../crypto/sha1.cpp
../crypto/sha256.cpp
../crypto/sha512.cpp

main_test.cpp
)
