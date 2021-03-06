/* Opens the mount handle
 * Returns 1 if successful, 0 if the keys could not be read or -1 on error
 */
int mount_handle_open(
     mount_handle_t *mount_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	${library_name}_file_t *${mount_tool_source_type}            = NULL;
	system_character_t *basename_end = NULL;
	static char *function            = "mount_handle_open";
	size_t basename_length           = 0;
	size_t filename_length           = 0;
	int entry_index                  = 0;

	if( mount_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid mount handle.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	filename_length = system_string_length(
	                   filename );

	basename_end = system_string_search_character_reverse(
	                filename,
	                (system_character_t) LIBCPATH_SEPARATOR,
	                filename_length + 1 );

	if( basename_end != NULL )
	{
		basename_length = (size_t) ( basename_end - filename ) + 1;
	}
	if( basename_length > 0 )
	{
		if( mount_handle_set_basename(
		     mount_handle,
		     filename,
		     basename_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set basename.",
			 function );

			goto on_error;
		}
	}
	if( ${library_name}_file_initialize(
	     &${mount_tool_source_type},
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize ${mount_tool_source_type}.",
		 function );

		goto on_error;
	}
	if( mount_handle->key_data_is_set != 0 )
	{
		if( ${library_name}_file_set_keys(
		     ${mount_tool_source_type},
		     mount_handle->key_data,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set keys.",
			 function );

			goto on_error;
		}
	}
	else if( mount_handle->password != NULL )
	{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( ${library_name}_file_set_utf16_password(
		     ${mount_tool_source_type},
		     (uint16_t *) mount_handle->password,
		     mount_handle->password_length,
		     error ) != 1 )
#else
		if( ${library_name}_file_set_utf8_password(
		     ${mount_tool_source_type},
		     (uint8_t *) mount_handle->password,
		     mount_handle->password_length,
		     error ) != 1 )
#endif
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set password.",
			 function );

			goto on_error;
		}
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( ${library_name}_file_open_wide(
	     ${mount_tool_source_type},
	     filename,
	     ${library_name_upper_case}_OPEN_READ,
	     error ) != 1 )
#else
	if( ${library_name}_file_open(
	     ${mount_tool_source_type},
	     filename,
	     ${library_name_upper_case}_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open ${mount_tool_source_type}.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     mount_handle->${mount_tool_source_type}s_array,
	     &entry_index,
	     (intptr_t *) ${mount_tool_source_type},
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append ${mount_tool_source_type} to array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( ${mount_tool_source_type} != NULL )
	{
		${library_name}_file_free(
		 &${mount_tool_source_type},
		 NULL );
	}
	libcdata_array_empty(
	 mount_handle->${mount_tool_source_type}s_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &${library_name}_file_free,
	 NULL );

	return( -1 );
}

