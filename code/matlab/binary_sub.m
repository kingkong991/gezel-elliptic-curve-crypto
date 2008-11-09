function [out] = binary_sub(x, y)
% Binary subtraction of x and y.
%
% Input:
%   x, y: bitstring, MSB first
%
% Output:
%   out: bitstring, MSB first

% a - b = a + not b + 1

% Make b as long as a and invert (create 2's complement)
nY = [repmat(['0'], 1, numel(x) - numel(y)) y];
nY = strrep(nY, '0', '2');
nY = strrep(nY, '1', '0');
nY = strrep(nY, '2', '1');

C = binary_add(nY, ['1']);

out = binary_add(x, C);

% Remove 2's complement bit (MSB)
out = out(2:numel(out));

if (numel(out) == 0)
    out = ['0'];
end