/* BDD user-visible definitions */


#if !defined(_BDDUSERCPPH)
#define _BDDUSERCPPH


#include <stdio.h>
#include <memuser.h>


#if defined(__STDC__)
#define ARGS(args) args
#else
#define ARGS(args) ()
#endif


/* Types */

typedef struct bdd_ *bdd;
typedef struct bdd_manager_ *bdd_manager;
typedef struct block_ *block;


/* Return values for bdd_type */

#define BDD_TYPE_NONTERMINAL 0
#define BDD_TYPE_ZERO 1
#define BDD_TYPE_ONE 2
#define BDD_TYPE_POSVAR 3
#define BDD_TYPE_NEGVAR 4
#define BDD_TYPE_OVERFLOW 5
#define BDD_TYPE_CONSTANT 6


/* Error codes for bdd_undump_bdd */

#define BDD_UNDUMP_FORMAT 1
#define BDD_UNDUMP_OVERFLOW 2
#define BDD_UNDUMP_IOERROR 3
#define BDD_UNDUMP_EOF 4


/* Basic BDD routine declarations */

extern "C"  bdd bdd_one ARGS((bdd_manager));
extern "C"  bdd bdd_zero ARGS((bdd_manager));
extern "C"  bdd bdd_new_var_first ARGS((bdd_manager));
extern "C"  bdd bdd_new_var_last ARGS((bdd_manager));
extern "C"  bdd bdd_new_var_before ARGS((bdd_manager, bdd));
extern "C"  bdd bdd_new_var_after ARGS((bdd_manager, bdd));
extern "C"  bdd bdd_var_with_index ARGS((bdd_manager, long));
extern "C"  bdd bdd_var_with_id ARGS((bdd_manager, long));
extern "C"  bdd bdd_ite ARGS((bdd_manager, bdd, bdd, bdd));
extern "C"  bdd bdd_and ARGS((bdd_manager, bdd, bdd));
extern "C"  bdd bdd_nand ARGS((bdd_manager, bdd, bdd));
extern "C"  bdd bdd_or ARGS((bdd_manager, bdd, bdd));
extern "C"  bdd bdd_nor ARGS((bdd_manager, bdd, bdd));
extern "C"  bdd bdd_xor ARGS((bdd_manager, bdd, bdd));
extern "C"  bdd bdd_xnor ARGS((bdd_manager, bdd, bdd));
extern "C"  bdd bdd_identity ARGS((bdd_manager, bdd));
extern "C"  bdd bdd_not ARGS((bdd_manager, bdd));
extern "C"  bdd bdd_if ARGS((bdd_manager, bdd));
extern "C"  long bdd_if_index ARGS((bdd_manager, bdd));
extern "C"  long bdd_if_id ARGS((bdd_manager, bdd));
extern "C"  bdd bdd_then ARGS((bdd_manager, bdd));
extern "C"  bdd bdd_else ARGS((bdd_manager, bdd));
extern "C"  bdd bdd_intersects ARGS((bdd_manager, bdd, bdd));
extern "C"  bdd bdd_implies ARGS((bdd_manager, bdd, bdd));
extern "C"  int bdd_type ARGS((bdd_manager, bdd));
extern "C"  void bdd_unfree ARGS((bdd_manager, bdd));
extern "C"  void bdd_free ARGS((bdd_manager, bdd));
extern "C"  long bdd_vars ARGS((bdd_manager));
extern "C"  long bdd_total_size ARGS((bdd_manager));
extern "C"  int bdd_cache_ratio ARGS((bdd_manager, int));
extern "C"  long bdd_node_limit ARGS((bdd_manager, long));
extern "C"  int bdd_overflow ARGS((bdd_manager));
extern "C"  void bdd_overflow_closure ARGS((bdd_manager, void (*) ARGS((bdd_manager, pointer)), pointer));
extern "C"  void bdd_abort_closure ARGS((bdd_manager, void (*) ARGS((bdd_manager, pointer)), pointer));
extern "C"  void bdd_stats ARGS((bdd_manager, FILE *));
extern "C"  bdd_manager bdd_init ARGS((void));
extern "C"  char *bdd_version ARGS((void));
extern "C"  void bdd_quit ARGS((bdd_manager));


/* Variable association routine declarations */

extern "C"  int bdd_new_assoc ARGS((bdd_manager, bdd *, int));
extern "C"  void bdd_free_assoc ARGS((bdd_manager, int));
extern "C"  void bdd_temp_assoc ARGS((bdd_manager, bdd *, int));
extern "C"  void bdd_augment_temp_assoc ARGS((bdd_manager, bdd *, int));
extern "C"  int bdd_assoc ARGS((bdd_manager, int));


/* Comparison routine declarations */

extern "C"  int bdd_compare ARGS((bdd_manager, bdd, bdd, bdd));


/* Composition routine declarations */

extern "C"  bdd bdd_compose ARGS((bdd_manager, bdd, bdd, bdd));
extern "C"  bdd bdd_substitute ARGS((bdd_manager, bdd));


/* Variable exchange routine declarations */

extern "C"  bdd bdd_swap_vars ARGS((bdd_manager, bdd, bdd, bdd));


/* Quantification routine declarations */

extern "C"  bdd bdd_exists ARGS((bdd_manager, bdd));
extern "C"  bdd bdd_forall ARGS((bdd_manager, bdd));


/* Reduce routine declarations */

extern "C"  bdd bdd_reduce ARGS((bdd_manager, bdd, bdd));
extern "C"  bdd bdd_cofactor ARGS((bdd_manager, bdd, bdd));


/* Relational product routine declarations */

extern "C"  bdd bdd_rel_prod ARGS((bdd_manager, bdd, bdd));


/* Satisfying valuation routine declarations */

extern "C"  bdd bdd_satisfy ARGS((bdd_manager, bdd));
extern "C"  bdd bdd_satisfy_support ARGS((bdd_manager, bdd));
extern "C"  double bdd_satisfying_fraction ARGS((bdd_manager, bdd));


/* Generic apply routine declarations */

extern "C"  bdd bdd_apply2 ARGS((bdd_manager, bdd (*) ARGS((bdd_manager, bdd *, bdd *, pointer)), bdd, bdd, pointer));
extern "C"  bdd bdd_apply1 ARGS((bdd_manager, bdd (*) ARGS((bdd_manager, bdd *, pointer)), bdd, pointer));


/* Size and profile routine declarations */

extern "C"  long bdd_size ARGS((bdd_manager, bdd, int));
extern "C"  long bdd_size_multiple ARGS((bdd_manager, bdd *, int));
extern "C"  void bdd_profile ARGS((bdd_manager, bdd, long *, int));
extern "C"  void bdd_profile_multiple ARGS((bdd_manager, bdd *, long *, int));
extern "C"  void bdd_function_profile ARGS((bdd_manager, bdd, long *));
extern "C"  void bdd_function_profile_multiple ARGS((bdd_manager, bdd *, long *));


/* Print routine declarations */

#if defined(__STDC__)
#define bdd_naming_fn_none ((char *(*)(bdd_manager, bdd, pointer))0)
#define bdd_terminal_id_fn_none ((char *(*)(bdd_manager, INT_PTR, INT_PTR, pointer))0)
#else
#define bdd_naming_fn_none ((char *(*)())0)
#define bdd_terminal_id_fn_none ((char *(*)())0)
#endif

extern "C"  void bdd_print_bdd ARGS((bdd_manager,
				bdd,
				char *(*) ARGS((bdd_manager, bdd, pointer)),
				char *(*) ARGS((bdd_manager, INT_PTR, INT_PTR, pointer)),
				pointer,
				FILE *));
extern "C"  void bdd_print_profile_aux ARGS((bdd_manager,
					long *,
					char *(*) ARGS((bdd_manager, bdd, pointer)),
					pointer,
					int,
					FILE *));
extern "C"  void bdd_print_profile ARGS((bdd_manager,
				    bdd,
				    char *(*) ARGS((bdd_manager, bdd, pointer)),
				    pointer,
				    int,
				    FILE *));
extern "C"  void bdd_print_profile_multiple ARGS((bdd_manager,
					     bdd *,
					     char *(*) ARGS((bdd_manager, bdd, pointer)),
					     pointer,
					     int,
					     FILE *));
extern "C"  void bdd_print_function_profile ARGS((bdd_manager,
					     bdd,
					     char *(*) ARGS((bdd_manager, bdd, pointer)),
					     pointer,
					     int,
					     FILE *));
extern "C"  void bdd_print_function_profile_multiple ARGS((bdd_manager,
						      bdd *,
						      char *(*) ARGS((bdd_manager, bdd, pointer)),
						      pointer,
						      int,
						      FILE *));


/* Dump/undump routine declarations */

extern "C"  int bdd_dump_bdd ARGS((bdd_manager, bdd, bdd *, FILE *));
extern "C"  bdd bdd_undump_bdd ARGS((bdd_manager, bdd *, FILE *, int *));


/* Support routine declarations */

extern "C"  int bdd_depends_on ARGS((bdd_manager, bdd, bdd));
extern "C"  void bdd_support ARGS((bdd_manager, bdd, bdd *));


/* Unique table routine declarations */

extern "C"  void bdd_gc ARGS((bdd_manager));
extern "C"  void bdd_clear_refs ARGS((bdd_manager));


/* Dynamic reordering routines */

#if defined(__STDC__)
#define bdd_reorder_none ((void (*)(bdd_manager))0)
#else
#define bdd_reorder_none ((void (*)())0)
#endif

extern "C"  void bdd_reorder_stable_window3 ARGS((bdd_manager));
extern "C"  void bdd_reorder_sift ARGS((bdd_manager));
extern "C"  void bdd_reorder_hybrid ARGS((bdd_manager));
extern "C"  void bdd_var_block_reorderable ARGS((bdd_manager, block, int));
extern "C"  void bdd_dynamic_reordering ARGS((bdd_manager, void (*) ARGS((bdd_manager))));
extern "C"  void bdd_reorder ARGS((bdd_manager));


/* Variable block routines */

extern "C"  block bdd_new_var_block ARGS((bdd_manager, bdd, long));


/* Multi-terminal BDD routine declarations */

extern "C"  void mtbdd_transform_closure ARGS((bdd_manager,
					  int (*) ARGS((bdd_manager, INT_PTR, INT_PTR, pointer)),
					  void (*) ARGS((bdd_manager, INT_PTR, INT_PTR, INT_PTR *, INT_PTR *, pointer)),
					  pointer));
extern "C"  void mtbdd_one_data ARGS((bdd_manager, INT_PTR, INT_PTR));
extern "C"  void mtbdd_free_terminal_closure ARGS((bdd_manager,
					      void (*) ARGS((bdd_manager, INT_PTR, INT_PTR, pointer)),
					      pointer));
extern "C"  bdd mtbdd_get_terminal ARGS((bdd_manager, INT_PTR, INT_PTR));
extern "C"  void mtbdd_terminal_value ARGS((bdd_manager, bdd, INT_PTR *, INT_PTR *));
extern "C"  bdd mtbdd_ite ARGS((bdd_manager, bdd, bdd, bdd));
extern "C"  bdd mtbdd_equal ARGS((bdd_manager, bdd, bdd));
extern "C"  bdd mtbdd_substitute ARGS((bdd_manager, bdd));
#define mtbdd_transform(bddm, f) (bdd_not(bddm, f))


#undef ARGS

#endif
