% 	Copyright (C) 2016 Alexandros Tsonis, Sotiris Papatheodorou
% 
% 	This file is part of NeuroticNetwork.
% 
% 	NeuroticNetwork is free software: you can redistribute it and/or modify
% 	it under the terms of the GNU General Public License as published by
% 	the Free Software Foundation, either version 3 of the License, or
% 	(at your option) any later version.
% 
% 	NeuroticNetwork is distributed in the hope that it will be useful,
% 	but WITHOUT ANY WARRANTY; without even the implied warranty of
% 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% 	GNU General Public License for more details.
% 
% 	You should have received a copy of the GNU General Public License
% 	along with NeuroticNetwork.  If not, see <http://www.gnu.org/licenses/>.


clear variables
close all

basename = 'nw';

i = 0;

while true
    fname=sprintf( [basename '%d.txt'], i);
    if exist(fname, 'file')
        w=importdata(fname);
    else
        break
    end

    numin=w(1,1);
    figure

    for j=1:numin
        subplot(numin,1,j)
        plot( w(2:end,j) )
        
        ylabel( sprintf('Weight %d',j) )
        if j == 1
            title(fname)
        end
    end
    xlabel('Iteration')

    i = i + 1;
end
