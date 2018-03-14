%% Keeping in a matrix only the rows which index is specified in 
%% horizontal vector r

function B = keeprows(A,r)
    sa = size(A);
    sr = size(r);
    B = zeros(sr(2),sa(2));
    for i =1:sr(2)
        B(i,:) = A(r(i),:);
    end
    