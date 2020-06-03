.name "CDMQPBLCLPB"
.comment "Je suis nul !"

st r1, 16
st r2, -5
and r2, r2, r1
live %1
fork %1023
zjmp %-8
