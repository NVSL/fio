#ifndef PMEM_BUFFER_H
#define PMEM_BUFFER_H

int create_pmem_pool(const char* dir, ssize_t buf_file_size, int num_files);
int close_pmem_pool(void);
int get_pmem_buffer(size_t buf_size, void** out_buf, int *out_fd, 
		off_t *out_offset);
int get_pmem_buffer_per_cpu(size_t buf_size, void** out_buf, int *out_fd, 
		off_t *out_offset, int cpu);

/* punch and patch */
#define NOVA_MOVE_OP    0xBCD00030

struct move_metadata {
    int src_fd;
    off_t src_offset;
    int dst_fd;
    off_t dst_offset;
    size_t len;
    int mark_hole;
};

struct punch_metadata {
    void *buf;
    size_t len;
    int fd;
    off_t offset;
    int mark_hole;
};

int __sz_move(int src_fd, off_t src_offset,
        int dst_fd, off_t dst_offset, size_t len, int mark_hole);
int __sz_punch(struct punch_metadata *p, size_t len, int mark_hole);
int __sz_punch_per_cpu(struct punch_metadata *p, size_t len, int mark_hole, int cpu);
int __sz_patch(int fd, off_t offset, struct punch_metadata *p);

#endif
