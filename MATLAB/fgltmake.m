function fgltmake (what)
%GBMAKE compile MATLAB interface for Fast Graphlet Transform
%
% Usage:
%   fgtmake
%
% See also mex, version.

have_octave = (exist ('OCTAVE_VERSION', 'builtin') == 5) ;

if (have_octave)
    if verLessThan ('octave', '7')
        gb_error ('Octave 7 or later is required') ;
    end
else
    if verLessThan ('matlab', '9.4')
        error ('MATLAB 9.4 (R2018a) or later is required') ;
    end
end

if (nargin < 1)
    what = '' ;
end

make_all = (isequal (what, 'all')) ;

if (have_octave)
    %% Octave does not have the new MEX classdef object and as of
    %% version 7, the mex command doesn't handle compiler options
    %% the same way as MATLAB's mex command.

    % use -R2018a for the new interleaved complex API
    flags = '-g -O -R2018a -std=c11 -fopenmp -fPIC -Wno-pragmas' ;
else
    % use -R2018a for the new interleaved complex API
    flags = '-g -O -R2018a' ;

    try
        if (strncmp (computer, 'GLNX', 4))
            % remove -ansi from CFLAGS and replace it with -std=c11
            cc = mex.getCompilerConfigurations ('C++', 'Selected') ;
            env = cc.Details.SetEnv ;
            c1 = strfind (env, 'CFLAGS=') ;
            q = strfind (env, '"') ;
            q = q (q > c1) ;
            if (~isempty (c1) && length (q) > 1)
                c2 = q (2) ;
                cflags = env (c1:c2) ;  % the CFLAGS="..." string
                ansi = strfind (cflags, '-ansi') ;
                if (~isempty (ansi))
                    cflags = [cflags(1:ansi-1) '-std=c11' cflags(ansi+5:end)] ;
                    flags = [flags ' ' cflags] ;
                    fprintf ('compiling with -std=c11 instead of default -ansi\n') ;
                end
            end
        end
    catch
    end
    if (~ismac && isunix)
        flags = [ flags   ' CFLAGS="$CXXFLAGS -fopenmp -fPIC -Wno-pragmas" '] ;
        flags = [ flags ' CXXFLAGS="$CXXFLAGS -fopenmp -fPIC -Wno-pragmas" '] ;
        flags = [ flags  ' LDFLAGS="$LDFLAGS  -fopenmp -fPIC" '] ;
    end
end

if ispc
    % Windows
    object_suffix = '.obj' ;
else
    % Linux, Mac
    object_suffix = '.o' ;
end

inc = '-I../build/' ;

ldflags      = '../build/libfglt.a' ;
ldflags_cilk = '-lcilkrts ../build/libfglt.a' ;

hfiles = [ dir('*.h') ; dir('util/*.h') ] ;

cfiles = dir ('util/*.c') ;

% Find the last modification time of any hfile.
% These are #include'd into source files.
htime = 0 ;
for k = 1:length (hfiles)
    t = datenum (hfiles (k).date) ;
    htime = max (htime, t) ;
end

% compile objects
[~,stdout] = system( 'make' );
if (strfind(stdout, 'make: Nothing to be done for `all'))
  any_c_compiled = false ;
else
  any_c_compiled = true ;
end

% compile any source files that need compiling
mexfunctions = dir ('mexfunctions/*.cpp') ;

mex -setup C++

% compile the mexFunctions
for k = 1:length (mexfunctions)

    % get the mexFunction filename and modification time
    mexfunc = mexfunctions (k).name ;
    mexfunction = [(mexfunctions (k).folder) filesep mexfunc] ;
    tc = datenum (mexfunctions(k).date) ;

    % get the compiled mexFunction modification time
    mexfunction_compiled = [ mexfunc(1:end-4) '.' mexext ] ;
    dobj = dir (mexfunction_compiled) ;
    if (isempty (dobj))
        % there is no compiled mexFunction; it must be compiled
        tobj = 0 ;
    else
        tobj = datenum (dobj.date) ;
    end

    % compile if it is newer than its object file, or if any cfile was compiled
    if (make_all || tc > tobj || any_c_compiled)
        % compile the mexFunction
        mexcmd = sprintf ('mex %s -silent %s %s ''%s'' -outdir ./', ...
            ldflags_cilk, flags, inc, mexfunction) ;
        fprintf ('%s\n', mexcmd) ;
        try
          eval (mexcmd) ;
        catch
          mexcmd = sprintf ('mex %s -silent %s %s ''%s'' -outdir ./', ...
            ldflags, flags, inc, mexfunction) ;
          fprintf ('%s\n', mexcmd) ;
          fprintf (':') ;
          eval (mexcmd) ;
        end
    end
end

fprintf ('\n') ;

fprintf ('Compilation of the MATLAB interface to Fast Graphlet Transform is complete.\n') ;
fprintf ('Add the following commands to your startup.m file:\n\n') ;
here1 = cd ('./') ;
% addpath (pwd) ;
fprintf ('  addpath (''%s'') ;\n', pwd) ;
cd (here1) ;


end

