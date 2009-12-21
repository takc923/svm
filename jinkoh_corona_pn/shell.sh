#!/bin/sh
u=10
while [ $u -ne 26 ]
do
	./svm_learn -t 4 -u ${u} corona_train.txt corona_model_u${u}.txt
	./svm_classify corona_test.txt corona_model_u${u}.txt corona_result_u${u}.txt > corona_log_u${u}.txt
	u=`expr $u + 1`
done
