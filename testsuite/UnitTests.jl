using FGLT
using SparseArrays
using Test
using LightGraphs
using Match

function claw()

  g = SimpleGraph(4);
  add_edge!(g, 1, 2)
  add_edge!(g, 1, 3)
  add_edge!(g, 1, 4)
  return g
  
end

function paw()

  g = SimpleGraph(4);
  add_edge!(g, 1, 2)
  add_edge!(g, 1, 3)
  add_edge!(g, 1, 4)
  add_edge!(g, 2, 3)
  return g
  
end

function buildU3(U3, f)

  for x in eachrow(f)
    r = findlast(x .== 1) - 2
    U3[:,r] = x[3:5]
  end

  return U3
  
end


function buildU4(U4, f)

  for x in eachrow(f)
    r = findlast(x .== 1) - 5
    U4[:,r] = x[6:end]
  end

  return U4
  
end

function graphlet(name)

  @match name begin
    "node" => Graph(1,0)
    "edge" => Graph(2,1)
    "bifork" => PathGraph(3)
    "triangle" => CycleGraph(3)
    "gate" => PathGraph(4)
    "claw" => claw()
    "paw" => paw()
    "c4" => CycleGraph(4)
    "diamond" => smallgraph("diamond")
    "k4" => CompleteGraph(4)
  end

end

@testset "all graphs up to 4 nodes" begin

  # === 1-node graph
  U1 = ones(Int32, 1, 1);
  f, fn = fglt( adjacency_matrix( graphlet("node") ) )

  @testset "1-node graph" begin
    @test all( f .== fn )
    @test all( f .== [1 zeros(1,15)])
  end
  
  # === 2-node graphs
  U2 = ones(Int32, 1, 1);
  f, fn = fglt( adjacency_matrix( graphlet("edge") ) )

  @testset "2-node graph" begin
    @test all( f .== fn )
    @test all( f .== [1 1 zeros(1,14); 1 1 zeros(1,14)])
  end
  
  # === 3-node graphs
  U3 = zeros(Int32, 3, 3);

  @testset "3-node graphs" begin
    
    # bi-fork/path-2
    f, fn = fglt( adjacency_matrix( graphlet("bifork") ) )
    @test all( fn .== [1  1  1  0 zeros(1,12);
                       1  2  0  1 zeros(1,12);
                       1  1  1  0 zeros(1,12)])

    U3 = buildU3(U3, f)

    # triangle
    f, fn = fglt( adjacency_matrix(graphlet("triangle")) )
    @test all( fn .== repeat( [1  2  0  0  1  zeros(1,11)], outer = [3 1] ) )

    U3 = buildU3(U3, f)

  end
    
  # === 4-node graphs
  U4 = zeros(Int32, 11, 11);
  
  f, fn = fglt( adjacency_matrix(graphlet("gate")) )
  U4 = buildU4(U4, f)
  f, fn = fglt( adjacency_matrix( graphlet("claw") ) )
  U4 = buildU4(U4, f)
  f, fn = fglt( adjacency_matrix(graphlet("paw")) )
  U4 = buildU4(U4, f)
  f, fn = fglt( adjacency_matrix( graphlet("c4") ) )
  U4 = buildU4(U4, f)
  f, fn = fglt( adjacency_matrix(graphlet("diamond")) )
  U4 = buildU4(U4, f)
  f, fn = fglt( adjacency_matrix( graphlet("k4") ) )
  U4 = buildU4(U4, f)

  # === build U16 conversion
  U16 = cat(U1, U2, U3, U4, dims=(1,2));

  U16_gold =
    [ 1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
      0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0
      0  0  1  0  2  0  0  0  0  0  0  0  0  0  0  0
      0  0  0  1  1  0  0  0  0  0  0  0  0  0  0  0
      0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0
      0  0  0  0  0  1  0  0  0  2  1  0  2  4  2  6
      0  0  0  0  0  0  1  0  0  0  1  2  2  2  4  6
      0  0  0  0  0  0  0  1  0  1  1  0  0  2  1  3
      0  0  0  0  0  0  0  0  1  0  0  1  0  0  1  1
      0  0  0  0  0  0  0  0  0  1  0  0  0  2  0  3
      0  0  0  0  0  0  0  0  0  0  1  0  0  2  2  6
      0  0  0  0  0  0  0  0  0  0  0  1  0  0  2  3
      0  0  0  0  0  0  0  0  0  0  0  0  1  1  1  3
      0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  3
      0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  3
      0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1];

  @testset "net-2-raw conversion" begin
    @test all( U16_gold .== U16 )
  end
end;

return nothing
