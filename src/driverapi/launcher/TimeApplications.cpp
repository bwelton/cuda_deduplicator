#include "TimeApplications.h"

TimeApplications::TimeApplications(boost::program_options::variables_map vm) :
	_vm(vm) {

}

double TimeApplications::InternalRun() {
	LogInfo log(std::string(""), std::string(""), false);
	ProcessController proc(_vm, &log);
	proc.LaunchProcess();
	assert(proc.ContinueExecution() == true);
	auto start = std::chrono::high_resolution_clock::now();
	while (!proc.IsTerminated()){
		proc.Run();
		assert(proc.ContinueExecution() == true);
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop-start;
	std::cerr << "[TIMEAPP] Application runtime without instrimentation - " << diff.count() << std::endl;
	return diff.count();	
}

double TimeApplications::Run() {
	// Run this twice to get rid of dyninst overhead....
	return InternalRun();
}

double TimeApplications::RunWithInstrimentation(std::string wrapperDef, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras) {
	LogInfo log(std::string("CUPTIRun.txt"), std::string("[CUPTI]"), true);
	ProcessController proc(_vm, &log);
	proc.LaunchProcess();
	for (auto i : extras)
		proc.InsertWrapperDef(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i), std::get<4>(i));
	proc.InsertInstrimentation(wrapperDef);
	proc.ContinueExecution();
	auto start = std::chrono::high_resolution_clock::now();
	while (!proc.IsTerminated()){
		proc.Run();
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop-start;
	std::cerr << "[TIMEAPP] Application runtime with instrimentation - " << diff.count() << std::endl;
	return diff.count();	
}

double TimeApplications::RunWithBreakpoints(std::string wrapperDef, 
											std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras,
											std::vector<std::string> breakFunctions,
											std::vector<std::string> libLoads,
											std::function<void(ProcessController *)> cb) {
	LogInfo log(std::string("BreakpointRun.txt"), std::string("[BPRun]"), true);
	ProcessController proc(_vm, &log);
	proc.LaunchProcess();
	for (auto i : extras)
		proc.InsertWrapperDef(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i), std::get<4>(i));
	proc.InsertInstrimentation(wrapperDef);
	for (auto i : libLoads) 
		proc.LoadWrapperLibrary(i);

	proc.InsertBreakpoints(breakFunctions);
	proc.ContinueExecution();
	auto start = std::chrono::high_resolution_clock::now();
	while (!proc.IsTerminated()){
		proc.Run();
		if (proc.IsStopped()){
			std::cerr << "[TIMEAPP] Breakpoint has been hit" << std::endl;
			cb(&proc);
			proc.ContinueExecution();
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop-start;
	std::cerr << "[TIMEAPP] Application runtime with instrimentation - " << diff.count() << std::endl;
	return diff.count();	
}


void TimeApplications::IdentifyDyninstBugs(std::string wrapperDef, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras, std::vector<std::string> libLoads) {
	std::vector<std::string> testerFunctions = {"__printf",
"__GI___libc_malloc",
"__GI_fwrite",
"__GI_exit",
"rand",
"__GI_fprintf",
"_IO_puts",
"__GI___libc_free",
"_Unwind_Resume",
"__stack_chk_fail",
"deregister_tm_clones",
"register_tm_clones",
"_IO_vfprintf_internal",
"get_free_list",
"_int_malloc",
"__lll_unlock_wake_private",
"__lll_lock_wait_private",
"arena_get2.part.3",
"arena_get_retry",
"__malloc_assert",
"__run_exit_handlers",
"__random",
"__GI_strlen",
"__overflow",
"_int_free",
"__munmap",
"__GI_abort",
"_itoa_word",
"__memset_sse2",
"__libc_message",
"__libgcc_s_init",
"__strchrnul",
"buffered_vfprintf",
"printf_positional",
"__GI_wcrtomb",
"__GI__IO_padn",
"targ1f8a8",
"__GI___assert_fail",
"group_number",
"_i18n_number_rewrite",
"__readonly_area",
"__GI___libc_fatal",
"strnlen",
"__GI___libc_alloca_cutoff",
"__wcsrtombs",
"targ1f8a0",
"__printf_fp",
"__printf_fphex",
"__GI___strerror_r",
"read_int",
"detach_arena.part.0",
"malloc_consolidate",
"sysmalloc",
"malloc_printerr",
"__get_nprocs",
"new_heap",
"__fxprintf",
"__GI__IO_fflush",
"__GI___call_tls_dtors",
"__GI__exit",
"__random_r",
"__GI_madvise",
"munmap_chunk",
"systrim.isra.2",
"__mmap64",
"__sigprocmask",
"_IO_flush_all_lockp",
"__GI_raise",
"__GI___sigaction",
"__fcloseall",
"__GI___libc_secure_getenv",
"__GI___mempcpy",
"backtrace_and_maps",
"__GI___libc_dlopen_mode",
"__GI___libc_dlsym",
"__parse_one_specmb",
"__GI___libc_scratch_buffer_grow_preserve",
"_dl_mcount_wrapper_check",
"__wcsmbs_load_conv",
"__GI___dcgettext",
"__assert_fail_base",
"__wctrans",
"__GI___towctrans",
"__memcpy_sse2",
"__new_fopen",
"getdelim",
"__strtoul",
"_IO_new_fclose",
"__wcsnlen",
"__wcslen",
"__GI___printf_fp_l",
"__woverflow",
"_IO_wpadn",
"__GI___mprotect",
"next_line",
"vfwprintf",
"__GI__IO_flush_all",
"__GI___libc_sigaction",
"_IO_cleanup",
"__GI_getenv",
"__GI___backtrace",
"__GI___backtrace_symbols_fd",
"__handle_registered_modifier_mb",
"__memalign",
"__strspn_sse42",
"__gconv_find_transform",
"__gconv_close_transform",
"__dcigettext",
"__GI___asprintf",
"__strcpy_sse2",
"__GI___libc_write",
"__GI___rawmemchr",
"__GI_strcmp",
"__fopen_internal",
"__GI___underflow",
"__memchr",
"__gconv_release_step",
"__GI__IO_un_link",
"_IO_new_file_close_it",
"__GI__IO_free_backup_area",
"__mpn_extract_long_double",
"__mpn_extract_double",
"__mpn_lshift",
"__guess_grouping",
"hack_digit",
"__mpn_mul_1",
"__mpn_mul",
"__mpn_divrem",
"__mpn_cmp",
"__mpn_rshift",
"__wmemmove",
"_i18n_number_rewrite",
"__wmemcpy",
"__wmemset",
"_IO_fwide",
"__memmove_sse2",
"__wcschrnul",
"buffered_vfprintf",
"printf_positional",
"__btowc",
"__mbsrtowcs",
"read_int",
"_i18n_number_rewrite",
"group_number",
"_IO_wsetb",
"__GI___sched_yield",
"__GI_strncmp",
"__writev",
"__GI__dl_addr",
"_int_memalign",
"__strspn_sse2",
"__gconv_lookup_cache",
"__GI___tfind",
"find_derivation",
"__gconv_read_conf",
"__gconv_release_cache",
"__current_locale_name",
"__getcwd",
"__GI_stpcpy",
"_nl_find_domain",
"_nl_find_msg",
"__GI_strchr",
"__GI___tsearch",
"plural_eval",
"_IO_vasprintf",
"__libc_enable_asynccancel",
"__libc_disable_asynccancel",
"_IO_no_init",
"_IO_new_file_init",
"__GI__IO_file_fopen",
"__fopen_maybe_mmap",
"save_for_backup",
"_IO_switch_to_main_get_area",
"__gconv_release_shlib",
"__GI__IO_unsave_markers",
"__GI__IO_free_wbackup_area",
"_IO_setb",
"__GI__IO_wdo_write",
"_IO_new_do_write",
"__mpn_addmul_1",
"__mpn_add_n",
"__mpn_impn_mul_n",
"__mpn_submul_1",
"__mpn_sub_n",
"__wcsmbs_clone_conv",
"_wordcopy_fwd_dest_aligned",
"_wordcopy_bwd_dest_aligned",
"_wordcopy_fwd_aligned",
"_wordcopy_bwd_aligned",
"__parse_one_specwc",
"__mbsrtowcs_l",
"__strncasecmp_avx",
"__hash_string",
"find_module",
"__gconv_get_builtin_trans",
"__gconv_find_shlib",
"__GI___strdup",
"__gconv_load_cache",
"__memcmp_sse2",
"add_module.isra.0",
"insert_module",
"__gconv_get_path",
"__GI___getpagesize",
"__GI___lxstat64",
"__fxstat64",
"__closedir",
"fdopendir",
"__readdir64",
"__GI___rewinddir",
"__GI___fxstatat64",
"_nl_make_l10nflist",
"_nl_load_domain",
"_nl_expand_alias",
"_nl_explode_name",
"__strstr_sse2",
"__gconv_open",
"__gconv",
"_IO_str_init_static_internal",
"__pthread_unwind",
"_IO_old_init",
"_IO_link_in",
"__GI__IO_file_open",
"__wcsmbs_named_conv",
"_IO_least_marker",
"__GI___twalk",
"__GI__IO_adjust_column",
"__mpn_impn_mul_n_basecase",
"__handle_registered_modifier_wc",
"__strncasecmp_l_nonascii",
"__GI___read",
"__GI_strtoll",
"__GI___fcntl",
"__alloc_dir",
"__getdents",
"__lseek64",
"__gettext_extract_plural",
"__GI___strcasecmp_l",
"read_alias_file",
"_nl_normalize_codeset",
"two_way_long_needle",
"nss_load_library",
"__GI___tdelete",
"__GI___open64",
"trecurse",
"__GI_____strtoll_l_internal",
"__gettextparse",
"__strcasecmp_l_nonascii",
"__GI___fgets_unlocked",
"__GI_qsort",
"__snprintf",
"__correctly_grouped_prefixmb",
"__gettext_free_exp",
"_IO_getline",
"__qsort_r",
"vsnprintf",
"__GI__IO_getline_info",
"msort_with_tmp.part.0",
"_quicksort",
"__GI___sysconf",
"__GI___uflow",
"__GI__IO_sputbackc",
"__cache_sysconf",
"__GI_getrlimit64",
"__get_child_max",
"__getclktck",
"__getdtablesize",
"__tzname_max",
"__sysconf_check_spec",
"__get_nprocs_conf",
"get_phys_pages",
"__get_avphys_pages",
"handle_amd",
"handle_intel",
"__tzfile_read",
"__tzset_parse_tz",
"_xstat",
"__opendir",
"__GI___sysinfo",
"intel_check_word",
"__GI___fileno",
"__fread_unlocked",
"__GI_fseek",
"__ftello",
"__tzstring",
"parse_tzname",
"_IO_sscanf",
"compute_offset",
"parse_rule",
"__tzfile_default",
"__GI__IO_sgetn",
"_IO_seekoff_unlocked",
"_IO_vsscanf",
"__GI__IO_vfscanf",
"__GI___mbrlen",
"__strtoll_internal",
"__GI___libc_scratch_buffer_set_array_size",
"mbrtoc32",
"__GI___strtod_internal",
"__GI___strtoul_internal",
"__GI___strtof_internal",
"__GI___strtold_internal",
"char_buffer_add_slow",
"__GI_____strtod_l_internal",
"__GI_____strtoull_l_internal",
"____strtof_l_internal",
"____strtold_l_internal",
"__strncasecmp_l_sse2",
"round_and_return",
"str_to_mpn.isra.0",
"__GI___strtod_nan",
"round_and_return",
"str_to_mpn.isra.0",
"__GI___strtof_nan",
"round_and_return",
"str_to_mpn.isra.0",
"__GI___strtold_nan",
"__mpn_construct_double",
"__mpn_construct_float",
"__mpn_construct_long_double"};
	LogInfo outLog(std::string("NonworkingCalls.txt"), std::string("[NonWorking]"), true);
	for (auto n : testerFunctions) {
		remove("run_done.txt");
		LogInfo log(std::string("LoadStoreRun.txt"), std::string("[LSRUN]"), true);
		ProcessController proc(_vm, &log);
		proc.LaunchProcess();
		// proc.InsertLoadStores();
		for (auto i : libLoads) 
			proc.LoadWrapperLibrary(i);
		proc.InsertLoadStoreSingle(std::string(n));
		// for (auto i : extras)
		// 	proc.InsertWrapperDef(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i), std::get<4>(i));
		// proc.InsertInstrimentation(wrapperDef);
		
		std::vector<std::string> bpoints;
		bpoints.push_back(std::string("SYNCH_SIGNAL_DYNINST"));
		bpoints.push_back(std::string("SYNC_RECORD_MEM_ACCESS"));
		bpoints.push_back(std::string("SYNC_RECORD_FUNCTION_ENTRY"));

		//proc.InsertBreakpoints(bpoints);
		proc.ContinueExecution();
		bool inserted = true;
		auto start = std::chrono::high_resolution_clock::now();
		while (!proc.IsTerminated()){
			proc.Run();

			if (proc.IsStopped()) {
				// std::cerr << "Hit breakpoint" << std::endl;
				// std::map<uint64_t, std::vector<StackPoint> > stackmap = proc.GetThreadStacks();
				// for (auto i : stackmap) {
				// 	std::cerr << "Stack length: " << i.second.size() << std::endl;
				// }
				proc.ContinueExecution();
			}

		}
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = stop-start;
		std::cerr << "[TIMEAPP] Application runtime with instrimentation - " << diff.count() << std::endl;
		bool badCall = false;
	    if (FILE *file = fopen("run_done.txt", "r")) {
	        fclose(file);
	    } else {
	        badCall = true;
	    }   
	    if (badCall == true){
	    	std::stringstream ss;
	    	ss << n;
	    	outLog.Write(ss.str());
	    	std::cerr << n << " has failed" << std::endl;
	    }
	}

}

double TimeApplications::RunWithLoadStore(std::string wrapperDef, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string> > extras, std::vector<std::string> libLoads) {
	LogInfo log(std::string("LoadStoreRun.txt"), std::string("[LSRUN]"), true);
	ProcessController proc(_vm, &log);
	proc.LaunchProcess();
	// proc.InsertLoadStores();
	for (auto i : libLoads) 
		proc.LoadWrapperLibrary(i);
	proc.InsertLoadStores();
	// for (auto i : extras)
	// 	proc.InsertWrapperDef(std::get<0>(i), std::get<1>(i), std::get<2>(i), std::get<3>(i), std::get<4>(i));
	// proc.InsertInstrimentation(wrapperDef);
	
	std::vector<std::string> bpoints;
	bpoints.push_back(std::string("SYNCH_SIGNAL_DYNINST"));
	bpoints.push_back(std::string("SYNC_RECORD_MEM_ACCESS"));
	bpoints.push_back(std::string("SYNC_RECORD_FUNCTION_ENTRY"));

	//proc.InsertBreakpoints(bpoints);
	proc.ContinueExecution();
	bool inserted = true;
	auto start = std::chrono::high_resolution_clock::now();
	while (!proc.IsTerminated()){
		proc.Run();

		if (proc.IsStopped()) {
			// std::cerr << "Hit breakpoint" << std::endl;
			// std::map<uint64_t, std::vector<StackPoint> > stackmap = proc.GetThreadStacks();
			// for (auto i : stackmap) {
			// 	std::cerr << "Stack length: " << i.second.size() << std::endl;
			// }
			proc.ContinueExecution();
		}

	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop-start;
	std::cerr << "[TIMEAPP] Application runtime with instrimentation - " << diff.count() << std::endl;
	return diff.count();	
}

