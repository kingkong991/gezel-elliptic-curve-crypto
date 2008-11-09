function [T] = montgomery_bit_serial(x, y, n)
% Calculates a Montgomery modular multiplication in 
% a bit serial fashion.
% 
% Input:
%   x = (x_(k-1), ..., x_0)_2
%   y = (y_(k-1), ..., y_0)_2
%   n = (n_(k-1), ..., n_0)_2, with gcd(n, 2) = 1
%
%   Thus x, y and n should be bitstrings MSB first.
%
% Output:
%   out = x * y * R^-1 mod n in bitstring format
%       where R = 2^k
%
% Thus, to get out = x * y mod n, do:
%   1. X = montgomery_bit_serial(x, 2^(2k), n)
%          Note that 2^(2k) > n, thus z = 2^(2k) mod n should be calculated
%          first and substituted in place of 2^(2k). Since z is fixed, this
%          shouldn't be a problem.
%   2. Y = montgomery_bit_serial(y, 2^(2k), n)
%   3. A = montgomery_bit_serial(X, Y, n)
%   4. out = montgomery_bit_serial(A, 1, n)

% Algorithm below, don't touch

% Some checks first
if (binary_cmp(n, x) < 1) || (binary_cmp(n, y) < 1)
    error('Error: 0 <= x, y < n should be true.');
end

if n(numel(n)) ~= '1'
    error('Error: gcd(n, 2) = 1 should be true.');
end

% Do serial-wise multiplication
k = numel(n);

X = sscanf(fliplr([repmat(['0'], 1, k - numel(x)) x]), '%1d')';  % Make X as long as N
Y = sscanf(fliplr(y), '%1d')';

% MSB bitstring representation of result
T = ['0'];

% Indices are all + 1, since MATLAB starts counting at 1 instead of 0.
for i = 0:(k - 1)
    m = xor(bin2dec(T(numel(T))), X(i + 1) & Y(1));
    
    if X(i + 1) == 1
        T = binary_add(T, y);
    end
    
    if m == 1
        T = binary_add(T, n);
    end
    
    % Divide by 2
    T = T(1:numel(T) - 1);
    
    if numel(T) == 0
        T = ['0'];
    end
end

if (binary_cmp(T, n) >= 0)
    T = binary_sub(T, n);
end