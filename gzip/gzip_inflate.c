#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include <zlib.h>


int main (void)

{

    z_stream zstream;
    char *outbuf;
    int n;
    int v;
    FILE *fp;

    n = 64 * 1024;

    zstream.next_in = malloc(n);
    assert(zstream.next_in != NULL);
    zstream.avail_in = n;
    zstream.total_in = 0;

    outbuf = malloc(n);
    zstream.next_out = (Bytef *)outbuf;
    assert(zstream.next_out != NULL);
    zstream.avail_out = n ;
    zstream.total_out = 0;

    zstream.msg = NULL;
    zstream.state = NULL;

    zstream.zalloc = NULL;
    zstream.zfree = NULL;

    fp = fopen("/tmp/out.gz", "rb");
    v = fread(zstream.next_in, 1, n, fp);
    printf("read: %d\n", v);
    assert(v > 0);
    fclose(fp);
    
    v = inflateInit2(&zstream, 32+15);
    assert(v == Z_OK);

    v = inflate(&zstream, Z_FINISH);
    assert(v == Z_STREAM_END);

    fp = fopen("/tmp/out", "wb");
    v = fwrite(outbuf, 1, zstream.total_out, fp);
    printf("wrote: %d\n", v);
    assert(v > 0);
    fclose(fp);

    v = inflateEnd(&zstream);
    assert(v == Z_OK);

    return 0;

}
