clear
close all

%% PARAMETERS
n = 100000;
iter = 5;

tOrca = zeros(iter,8);
tFGLT = zeros(iter,8);
maxDeg = zeros(iter,8);
discr = zeros(iter,8);

for p = 1:8
  for k = 1:iter
    %     A = sprand(n,n,p/n);
    %     A = sparse( logical( A+A' ) );
    %     A = A - diag(diag(A));
    
    A = createRandRegGraph(n,p);
    
    maxDeg(k,p) = max(sum(A));
    
    ticFGlT = tic;
    Fnet = fglt( A );
    tFGLT(k,p) = toc(ticFGlT);
    
    ticORCA = tic;
    G = graph.runOrca(A);
    tOrca(k,p) = toc(ticORCA);
    
    discr(k,p) = norm(G - Fnet, 'fro');
  end
  
  figure(1)
  semilogy([median(tOrca).' median(tFGLT).'],'o-')
  legend({'ORCA', 'FGLT'})
  xlabel('degree')
  ylabel('Time (sec)')
  drawnow
  
  figure(2)
  semilogy([min(tOrca).' median(tOrca).' max(tOrca).' ...
    min(tFGLT).' median(tFGLT).' max(tFGLT).'],'o-')
  
  drawnow
end

fprintf('All correct ? %d\n', ...
  all(discr(:) == 0))
