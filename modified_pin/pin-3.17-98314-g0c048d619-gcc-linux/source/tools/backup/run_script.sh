// set this first!!!
PIN_ROOT='/home/emily/Documents/computer_architecture/modified_pin/pin-3.17-98314-g0c048d619-gcc-linux'

// example
// first, run program
//python hello_world.py
// second, run using pin
//$PIN_ROOT/pin -t obj-intel64/pintool.so -- python hello_world.py > hello_world_trace.txt

./matrix
$PIN_ROOT/pin -t obj-intel64/pintool.so -- ./matrix > matrix_mult_trace.txt

//python matrix_mult.py
//$PIN_ROOT/pin -t obj-intel64/pintool.so -- python matrix_mult.py > matrix_mult_trace.txt

//python histograms.py
//$PIN_ROOT/pin -t obj-intel64/pintool.so -- python histograms.py > histograms_trace.txt

//python transitive_closure_of_a_graph.py 
//$PIN_ROOT/pin -t obj-intel64/pintool.so -- python transitive_closure_of_a_graph.py > transitive_closure_of_a_graph_trace.txt 
