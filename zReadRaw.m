%%USC ID Numberc: 4946-8507-13
%%USC Email: maorushe@usc. sedu
%%Submission Date: 10/11/2015
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%Problem 2 : (d)
%%This code is to read in edge image and ground truth
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%file zReadRaw
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

row=481;col=321;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% image_name='Cougar_canny1.raw';% Get file ID for file
% fid=fopen(image_name,'rb');% Check if file exists
% if (fid == -1)
%     error('can not open input image file press CTRL-C to exit \n');
% 	pause;
% end% Get all the pixels from the image
% pixel = fread(fid, inf, 'uchar');% Close file
% fclose(fid);
% E = reshape(pixel(1:1:end),row,col);
% for i=1:row
%     for j=1:col
%     if (E(i,j)==0)
%         E(i,j)=1;
%     else
%         E(i,j)=0;
%     end
%     end
% end
% E = double(E');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

image_name='Cougar_GT3.raw';
% Get file ID for file
fid=fopen(image_name,'rb');
% Check if file exists
if (fid == -1)
    error('can not open input image file press CTRL-C to exit \n');
	pause;
end
% Get all the pixels from the image
pixel = fread(fid, inf, 'uchar');
% Close file
fclose(fid);
GT = reshape(pixel(1:1:end),row,col);
for i=1:row
    for j=1:col
    if (GT(i,j)==255)
        GT(i,j)=0;
    else
        GT(i,j)=1;
    end
    end
end
GT = double(GT');