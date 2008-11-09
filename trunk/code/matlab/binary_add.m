function [out] = binary_add(x, y)
% Binary addition of x and y.
%
% Input:
%   x, y: bitstring, MSB first
%
% Output:
%   out: bitstring, MSB first

% Remove all 0's from the MSB side of the string
% and convert to correct representation
X = regexprep(x, '0*([01]*)', '$1');
Y = regexprep(y, '0*([01]*)', '$1');

k = max([numel(X) numel(Y)]);

% Make both strings equally long
X = sscanf(fliplr([repmat(['0'], 1, k - numel(X)) X]), '%1d');
Y = sscanf(fliplr([repmat(['0'], 1, k - numel(Y)) Y]), '%1d');

S = repmat([0], 1, k + 1);
C = 0;

% Simulate full adder, bitwise addition, carry propagate
for i = 1:k
    S(i) = xor(xor(X(i), Y(i)), C);
    C = or(and(X(i), Y(i)), and(C, xor(X(i), Y(i))));
end

% Save last carry
S(k + 1) = C;

% Trim result & return bitstring
out = regexprep(sprintf('%1d', fliplr(S)), '0*([01]*)', '$1');

if (numel(out) == 0)
    out = ['0'];
end