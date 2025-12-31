# this is a comment

# the following 3 lines are commands
#! start q0
#! end q12
#! fill B

# Now we specify some rules
q0 1 y R q1
q0 0 x R q8
q1 0 0 R q1
q1 1 1 R q1
q1 c c R q2
q2 x x R q2
q2 y y R q2
q2 0 x R q3
q2 1 y R q4
q3 0 0 R q3
q3 1 1 R q3
q3 c c R q3
q3 x x R q3
q3 y y R q3
q3 B x L q5
q4 0 0 R q4
q4 1 1 R q4
q4 c c R q4
q4 x x R q4
q4 y y R q4
q4 B y L q5
q5 x x L q5
q5 y y L q5
q5 c c L q6
q6 0 0 L q6
q6 1 1 L q6
q6 x x L q6
q6 y y L q6
q6 c c L q7
q7 0 0 L q7
q7 1 1 L q7
q7 x x R q0
q7 y y R q0
q8 0 0 R q8
q8 1 1 R q8
q8 c c R q9
q9 x x R q9
q9 y y R q9
q9 0 x R q3
q9 1 y R q3
q0 c c R q10
q10 x x R q10
q10 y y R q10
q10 c c R q10
q10 B B L q11
q11 x 0 L q11
q11 y 1 L q11
q11 c c L q11
q11 B B L q12


