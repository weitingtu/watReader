watReader
=========
The file WAT_report.txt is a typical WAT test report and you can find the format definition in file WAT_format.xlsx.
The test report contains 25 wafers, WF#1~25, each wafer are with 5 sites measurement, S#1~5.
Please develop a C program in your preferred compiler to read the WAT report, calculate the average of each parameter on each wafer, and output the results to an CSV file.
 
The resulted output file are with field name in the first row and should looks like below, and the output file name should be exactly the same with the lot no. in the report.
 
WF#,N+ 0.5*408 Rc,P+ 0.5*408 Rc,P1 0.5*520 RC,M1 800/0.6 RES,M2 800/0.7 RES,VIA .55*520 Rc,BVR GOX/NW@1uA,BVR,...
01,¡K
02,¡K