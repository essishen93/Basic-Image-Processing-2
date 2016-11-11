%%USC ID Numberc: 4946-8507-13
%%USC Email: maorushe@usc. sedu
%%Submission Date: 10/11/2015
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%Problem 2 : (d)
%%This code is to do the evaluation of the edge detection
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%functions newEvl
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [R,P,F] = newEvl( E, GT)
thin=1;
E1 = double(E>=max(eps,0.1));
  if(thin), E1=double(bwmorph(E1,'thin',inf)); end
  % compare to each ground truth in turn and accumualte
    [matchE1,matchG1] = correspondPixels(E1,GT(:,:,1),0.0075);
    matchE = matchE1>0; 
    matchG = double(matchG1>0);
    allG = GT(:,:,1);
  % compute recall (summed over each gt image)
  cntR = sum(matchG(:)); sumR = sum(allG(:));
  % compute precision (edges can match any gt image)
  cntP = nnz(matchE); sumP = nnz(E1);
  
  R = cntR./sumR;
  P = cntP./sumP;
  F = (2*R*P)/(R+P);
end