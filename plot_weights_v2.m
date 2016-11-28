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

% Loop over all layers
layers_exist = true;
layer = 1;
while layers_exist
    
    % Loop over each neuron in the layer
    neuron = 1;
    while true
        % Create file name and check if the file exists
        fname=sprintf( [basename '_%d_%d.txt'], layer, neuron);
        if exist(fname, 'file')
            w=importdata(fname);
        else
            if neuron == 0
                % There are no more layers
                layers_exist = false;
            end
            break
        end

        figure
        numin=w(1,1);

        for j=1:numin
            subplot(numin,1,j)
            plot( w(2:end,j) )

            % Plot labels
            ylabel( sprintf('Weight %d',j) )
            if j == 1
                title(sprintf('Layer %d Neuron %d', layer, neuron))
            elseif j == numin
                xlabel('Iteration')
            end
        end
        
        neuron = neuron + 1;
    end

    layer = layer + 1;
end
