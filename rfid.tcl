set ns [new Simulator ]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

set nf [open out.nam w]
$ns namtrace-all $nf
$ns duplex-link $n1 $n2 2mb 10ms DropTail
$ns duplex-link $n1 $n3 2mb 10ms DropTail
$ns duplex-link $n2 $n3 2mb 10ms DropTail

set ra [new Agent/RfidRAgent]
set ta1 [new Agent/RfidTAgent]
set ta2 [new Agent/RfidTAgent]

$ns attach-agent $n1 $ra
$ns attach-agent $n2 $ta1
#$ns attach-agent $n3 $ta2

$ns connect $ra $ta1
$ns connect $ra $ta2
$ns connect $ta1 $ta2

proc finish {} {}

$ns at 1.0 "$ra test"
$ns at 2.0 "finish"
