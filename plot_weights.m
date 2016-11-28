clear all;
close all;

names = readdir('.');

for i=3:(length(names)-1);
  names=char(names);
  w=importdata(names(i,:));
  numin=w(1,1);
  figure;
  
  for j=1:numin;
    subplot(numin,1,j);
    plot(w(2:rows(w),j));
    %ylabel("Weight %d",j);
   end
   %xlabel("Iteration"); 
   title(names(i,:));
 end