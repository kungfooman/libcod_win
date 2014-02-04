#include "../include/gsc_mysql.h"
#include "../include/functions.h"
#include "../include/gsc.h"

#if COMPILE_MYSQL == 1

/*
	Had the problem, that a query failed but no mysql_errno() was set
	Reason: mysql_query() didnt even got executed, because the str was undefined
	So the function quittet with stackReturnInt(0)
	Now its undefined, and i shall test it every time
*/

/*
	100 == mysql_init()
	101 == mysql_real_connect(mysql, host, user, pass, db, port)
	102 == mysql_close(mysql)
	103 == mysql_query(mysql, query)
	104 == mysql_errno(mysql)
	105 == mysql_error(mysql)
	106 == mysql_affected_rows(mysql)
	107 == mysql_store_result(mysql)
	108 == mysql_num_rows(result)
	109 == mysql_num_fields(result)
	110 == mysql_field_seek(result, position)
	111 == mysql_fetch_field()
	112 == mysql_fetch_row(result)
	113 == mysql_free_result(result)
*/

#include <mysql.h>

int gsc_mysql_init()
{
	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_init()\n");
	#endif
	MYSQL *my;
	my = mysql_init(NULL);
	int ret = (int) my;
	return stackReturnInt(ret);
}

int gsc_mysql_real_connect()
{
	int mysql;
	char *host;
	char *user;
	char *pass;
	char *db;
	int port;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	helper += stackGetParamString(2, &host);
	helper += stackGetParamString(3, &user);
	helper += stackGetParamString(4, &pass);
	helper += stackGetParamString(5, &db);
	helper += stackGetParamInt(6, &port);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_real_connect(mysql=%d, host=\"%s\", user=\"%s\", pass=\"%s\", db=\"%s\", port=%d)\n", mysql, host, user, pass, db, port);
	#endif

	if (helper != 6)
	{
		Com_Printf("scriptengine> wrongs args for mysql_real_connect(...);\n");
		return stackPushUndefined();
	}

	mysql = (int) mysql_real_connect((MYSQL *)mysql, host, user, pass, db, port, NULL, 0);

	return stackReturnInt(mysql);
}

int gsc_mysql_close()
{
	int mysql;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_close(%d)\n", mysql);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_close(mysql);\n");
		return stackPushUndefined();
	}

	mysql_close((MYSQL *)mysql);

	return stackReturnInt(0);
}

int gsc_mysql_query()
{
	int mysql;
	char *sql;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	helper += stackGetParamString(2, &sql);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_query(%d, \"%s\")\n", mysql, sql);
	#endif

	if (helper != 2)
	{
		Com_Printf("scriptengine> wrongs args for mysql_query(...);\n");
		return stackPushUndefined();
	}

	int ret = mysql_query((MYSQL *)mysql, sql);
	return stackReturnInt(ret);
}

int gsc_mysql_errno()
{
	int mysql;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_errno(%d)\n", mysql);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_close(mysql);\n");
		return stackPushUndefined();
	}

	int ret = mysql_errno((MYSQL *)mysql);
	return stackReturnInt(ret);
}

int gsc_mysql_error()
{
	int mysql;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_error(%d)\n", mysql);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_close(mysql);\n");
		return stackPushUndefined();
	}

	char *ret = (char *)mysql_error((MYSQL *)mysql);
	return stackPushString(ret);
}

int gsc_mysql_affected_rows()
{
	int mysql;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_affected_rows(%d)\n", mysql);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_affected_rows(mysql);\n");
		return stackPushUndefined();
	}

	int ret = mysql_affected_rows((MYSQL *)mysql);
	return stackReturnInt(ret);
}

int gsc_mysql_store_result()
{
	int mysql;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_store_result(%d)\n", mysql);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_store_result(mysql);\n");
		return stackPushUndefined();
	}

	MYSQL_RES *result;
	result = mysql_store_result((MYSQL *)mysql);

	int ret = (int) result;
	return stackReturnInt(ret);
}

int gsc_mysql_num_rows()
{
	int result;

	int helper = 0;
	helper += stackGetParamInt(1, &result);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_num_rows(result=%d)\n", result);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_num_rows(result);\n");
		return stackPushUndefined();
	}

	int ret = mysql_num_rows((MYSQL_RES *)result);
	return stackReturnInt(ret);
}

int gsc_mysql_num_fields()
{
	int result;

	int helper = 0;
	helper += stackGetParamInt(1, &result);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_num_fields(result=%d)\n", result);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_num_fields(result);\n");
		return stackPushUndefined();
	}

	int ret = mysql_num_fields((MYSQL_RES *)result);
	return stackReturnInt(ret);
}

int gsc_mysql_field_seek()
{
	int result;
	int offset;

	int helper = 0;
	helper += stackGetParamInt(1, &result);
	helper += stackGetParamInt(2, &offset);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_field_seek(result=%d, offset=%d)\n", result, offset);
	#endif

	if (helper != 2)
	{
		Com_Printf("scriptengine> wrongs args for mysql_field_seek(result, offset);\n");
		return stackPushUndefined();
	}

	int ret = mysql_field_seek((MYSQL_RES *)result, offset);
	return stackReturnInt(ret);
}

int gsc_mysql_fetch_field()
{
	int result;

	int helper = 0;
	helper += stackGetParamInt(1, &result);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_fetch_field(result=%d)\n", result);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_fetch_field(result);\n");
		return stackPushUndefined();
	}

	MYSQL_FIELD *field = mysql_fetch_field((MYSQL_RES *)result);
	if (field == NULL)
		return stackPushUndefined();
	char *ret = field->name;
	return stackPushString(ret);
}

int gsc_mysql_fetch_row()
{
	int result;

	int helper = 0;
	helper += stackGetParamInt(1, &result);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_fetch_row(result=%d)\n", result);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_fetch_row(result);\n");
		return stackPushUndefined();
	}

	MYSQL_ROW row = mysql_fetch_row((MYSQL_RES *)result);
	if (!row)
	{
		#if DEBUG_MYSQL
		Com_Printf("row == NULL\n");
		#endif
		return stackPushUndefined();
	}

	int ret = alloc_object_and_push_to_array();

	int numfields = mysql_num_fields((MYSQL_RES *)result);
	for (int i=0; i<numfields; i++)
	{
		if (row[i] == NULL)
			stackPushUndefined();
		else
			stackPushString(row[i]);

		#if DEBUG_MYSQL
		Com_Printf("row == \"%s\"\n", row[i]);
		#endif
		push_previous_var_in_array_sub();
	}

	return ret;
}

int gsc_mysql_free_result()
{
	int result;

	int helper = 0;
	helper += stackGetParamInt(1, &result);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_free_result(result=%d)\n", result);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for mysql_free_result(result);\n");
		return stackPushUndefined();
	}

	mysql_free_result((MYSQL_RES *)result);
	return stackPushUndefined();
}



int gsc_mysql_real_escape_string()
{
	int mysql;
	char *str;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql);
	helper += stackGetParamString(2, &str);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_real_escape_string(%d, \"%s\")\n", mysql, str);
	#endif

	if (helper != 2)
	{
		Com_Printf("scriptengine> wrongs args for mysql_real_escape_string(...);\n");
		return stackPushUndefined();
	}

	char *to = (char *) malloc(strlen(str) * 2 + 1);
	int ret = mysql_real_escape_string((MYSQL *)mysql, to, str, strlen(str));
	int retString = stackPushString(to);
	free(to);
	return retString;
}

/* FUNCTIONS OF PREPARED STATEMENTS */




int gsc_mysql_stmt_init()
{
	int mysql;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_init(mysql=%d)\n", mysql); // print as %d, cause i cant print it with hex in .gsc
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_init(mysql);\n");
		return stackReturnInt(0);
	}

	MYSQL_STMT *stmt;
	stmt = mysql_stmt_init((MYSQL*)mysql);

	int ret = (int) stmt;
	return stackReturnInt(ret);
}

int gsc_mysql_stmt_close()
{
	int mysql_stmt;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_close(mysql_stmt=%d)\n", mysql_stmt);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_close(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = (int) mysql_stmt_close((MYSQL_STMT*)mysql_stmt);
	return stackReturnInt(ret);
}

int gsc_mysql_stmt_get_stmt_id()
{
	int mysql_stmt;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_get_stmt_id(mysql_stmt=%d)\n", mysql_stmt);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_get_stmt_id(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = ((MYSQL_STMT*)mysql_stmt)->stmt_id;
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_get_prefetch_rows()
{
	int mysql_stmt;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_get_prefetch_rows(mysql_stmt=%d)\n", mysql_stmt);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_get_prefetch_rows(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = ((MYSQL_STMT*)mysql_stmt)->prefetch_rows;
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_get_param_count()
{
	int mysql_stmt;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_get_param_count(mysql_stmt=%d)\n", mysql_stmt);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_get_param_count(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = ((MYSQL_STMT*)mysql_stmt)->param_count;
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_get_field_count()
{
	int mysql_stmt;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_get_field_count(mysql_stmt=%d)\n", mysql_stmt);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_get_field_count(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = ((MYSQL_STMT*)mysql_stmt)->field_count;
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_prepare()
{
	int mysql_stmt;
	char *sql;
	int len;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	helper += stackGetParamString(2, &sql);
	helper += stackGetParamInt(3, &len);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_prepare(mysql_stmt=%d, sql=%s)\n", mysql_stmt, sql);
	#endif

	if (helper != 3)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_prepare(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_prepare((MYSQL_STMT*)mysql_stmt, sql, len);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_bind_param()
{
	int mysql_stmt;
	int param;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	helper += stackGetParamInt(2, &param);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_bind_param(mysql_stmt=%d, param=%d)\n", mysql_stmt, param);
	#endif

	if (helper != 2)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_bind_param(mysql_stmt, param);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_bind_param((MYSQL_STMT*)mysql_stmt, (MYSQL_BIND*)param);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_bind_result()
{
	int mysql_stmt;
	int result;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);
	helper += stackGetParamInt(2, &result);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_bind_result(mysql_stmt=%d, result=%d)\n", mysql_stmt, result);
	#endif

	if (helper != 2)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_bind_result(mysql_stmt, result);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_bind_result((MYSQL_STMT*)mysql_stmt, (MYSQL_BIND*)result);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_execute()
{
	int mysql_stmt;
	int result;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_execute(mysql_stmt=%d)\n", mysql_stmt);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_execute(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_execute((MYSQL_STMT*)mysql_stmt);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_store_result()
{
	int mysql_stmt;
	int result;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_store_result(mysql_stmt=%d)\n", mysql_stmt);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_store_result(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_store_result((MYSQL_STMT*)mysql_stmt);
	return stackReturnInt(ret);
}
int gsc_mysql_stmt_fetch()
{
	int mysql_stmt;
	int result;

	int helper = 0;
	helper += stackGetParamInt(1, &mysql_stmt);

	#if DEBUG_MYSQL
	Com_Printf("gsc_mysql_stmt_fetch(mysql_stmt=%d)\n", mysql_stmt);
	#endif

	if (helper != 1)
	{
		Com_Printf("scriptengine> wrongs args for gsc_mysql_stmt_fetch(mysql_stmt);\n");
		return stackReturnInt(0);
	}

	int ret = mysql_stmt_fetch((MYSQL_STMT*)mysql_stmt);
	return stackReturnInt(ret);
}

#endif // compile mysql
