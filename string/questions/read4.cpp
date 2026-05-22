/// Severity: Sev0
// Date: 17May26
// LC: 158
// Where I failed: implementation...
// Pattern: buffer, char array
// Notes: sev0..sev0..sev0..
// string s; char* c = s.data(): append kora jai na *c te.



/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    string buf4 = "";
    int buflocalidx = 0, bufidx = 0, buflocallen = 0;
    int read(char *buf, int n) {
        bufidx = 0;
        while(bufidx < n){
            if(buflocalidx == 0){
                buflocallen = read4(buf4.data());
            }
            if(buflocallen == 0) break;
            while((bufidx < n) && (buflocalidx < buflocallen)) {
                buf[bufidx++] = buf4[buflocalidx++];
            }
            if(buflocalidx >= buflocallen) {
                buflocalidx = 0;
                buf4 = "";
            }
        }
        return bufidx;
    }
};