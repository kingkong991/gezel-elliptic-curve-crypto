function [out] = binary_cmp(x, y)
% Binary comparison of x and y.
% 
% Input:
%   x, y: bitstring, MSB first
%
% Output:
%   x = y: 0
%   x < y: -1
%   x > y: 1

% Remove all 0's from the MSB side of the string
% and convert to correct representation
x = sscanf(regexprep(x, '0*([01]*)', '$1'), '%1d')';
y = sscanf(regexprep(y, '0*([01]*)', '$1'), '%1d')';

% Do comparison
if numel(x) < numel(y)
    out = -1;
    return
elseif numel(y) < numel(x)
    out = 1;
    return
else
    % Numbers have equal length, do bitwise comparison
    for i = 1:numel(x)
       if x(i) > y(i)
           out = 1;
           return
       elseif y(i) > x(i)
           out = -1;
           return
       end
    end

    out = 0;
    return
end