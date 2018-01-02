#ifndef HAVE_DEFINED_lock_H
#define HAVE_DEFINED_lock_H

// Automaticaly generated by script/produce_module_declaration_h.pl.

#if defined DEBUG


#endif

bool semaphore_available_p(s_semaphore_t *semaphore);
bool semaphore_illegal_p(s_semaphore_t *semaphore);
bool semaphore_legal_p(s_semaphore_t *semaphore);
bool spin_lock_available_p(s_spin_lock_t *spin_lock);
bool spin_lock_illegal_p(s_spin_lock_t *spin_lock);
bool spin_lock_legal_p(s_spin_lock_t *spin_lock);
bool spin_lock_locked_p(s_spin_lock_t *spin_lock);
s_semaphore_t * semaphore_create(uint32 val);
s_spin_lock_t * spin_lock_create(void);
static inline bool semaphore_available_ip(s_semaphore_t *semaphore);
static inline bool semaphore_illegal_ip(s_semaphore_t *semaphore);
static inline bool semaphore_legal_ip(s_semaphore_t *semaphore);
static inline bool spin_lock_illegal_ip(s_spin_lock_t *spin_lock);
static inline bool spin_lock_legal_ip(s_spin_lock_t *spin_lock);
static inline bool spin_lock_locked_ip(s_spin_lock_t *spin_lock);
static inline s_array_queue_t * semaphore_sleep_queue(s_semaphore_t *semaphore);
static inline s_spin_lock_t * semaphore_spin_lock(s_semaphore_t *semaphore);
static inline sint32 semaphore_val(s_semaphore_t *semaphore);
static inline uint32 spin_lock_shared_lock(s_spin_lock_t *spin_lock);
static inline void semaphore_destroy_i(s_semaphore_t *semaphore);
static inline void semaphore_down_i(s_semaphore_t *semaphore);
static inline void semaphore_up_i(s_semaphore_t *semaphore);
static inline void spin_lock_destroy_i(s_spin_lock_t *spin_lock);
static inline void spin_lock_initial_i(s_spin_lock_t *spin_lock);
static inline void spin_lock_release_i(s_spin_lock_t *spin_lock);
static inline void spin_lock_shared_lock_clear(s_spin_lock_t *spin_lock);
static inline void spin_lock_try_i(s_spin_lock_t *spin_lock);
static void semaphore_sigcont_handler(sint32 signum);
void semaphore_destroy(s_semaphore_t **semaphore);
void semaphore_down(s_semaphore_t *semaphore);
void semaphore_up(s_semaphore_t *semaphore);
void spin_lock_destroy(s_spin_lock_t **lock);
void spin_lock_initial(s_spin_lock_t *spin_lock);
void spin_lock_release(s_spin_lock_t *spin_lock);
void spin_lock_try(s_spin_lock_t *spin_lock);

#endif

