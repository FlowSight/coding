when you can avoid for loop do, flatten the loop.
Why?: for loop is slow, and it is not cache friendly.
like dirs ={ {0,1}, {1,0}, {0,-1}, {-1,0} };
dont do
for(auto dir : dirs) {
    int x = i + dir[0];
    int y = j + dir[1];
    // do something
}
instead do
function(x+1, y);
function(x-1, y);
function(x, y+1);
function(x, y-1);

//TODO : find out why??
