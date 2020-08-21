clear
close all

%% PARAMETERS
n = 100000;

tOrca = zeros(10,8);
tFGLT = zeros(10,8);
maxDeg = zeros(10,8);

for p = 1:8
  for k = 1:10
    A = sprand(n,n,p/n);
    A = sparse( logical( A+A' ) );
    A = A - diag(diag(A));
    
    maxDeg(k,p) = max(sum(A));
    
    ticFGlT = tic;
    Fnet = fglt( A );
    tFGLT(k,p) = toc(ticFGlT);
    
    ticORCA = tic;
    G = graph.runOrca(A);
    tOrca(k,p) = toc(ticORCA);
  end
end

