cxx_test(
   TARGET euclidean_vector_test1
   FILENAME "euclidean_vector_test1.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET utility_tests
   FILENAME "utility_tests.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET compare_tests
   FILENAME "compare_tests.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET index_tests
   FILENAME "index_tests.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET constructor_tests
   FILENAME "constructor_tests.cpp"
   LINK euclidean_vector
)

cxx_test(
   TARGET operation_tests
   FILENAME "operation_tests.cpp"
   LINK euclidean_vector
)