function [centroids] = clustering_pc(points, NC)
[indexes, clusterCentroids] = kmeans(points, NC);
  
endfunction
