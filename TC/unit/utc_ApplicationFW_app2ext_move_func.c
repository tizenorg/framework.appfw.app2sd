/*
 * app2ext
 *
 * Copyright (c) 2000 - 2012 Samsung Electronics Co., Ltd. All rights reserved.
 * Contact: Jyotsna Dhumale <jyotsna.a@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either expostss or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <tet_api.h>
#include <app2ext_interface.h>

static void startup(void);
static void cleanup(void);

char pkg_ro_content_rpm[3][5] = { "bin", "res", "lib" };

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;

static void utc_ApplicationFW_app2ext_move_func_01(void);
static void utc_ApplicationFW_app2ext_move_func_02(void);
static void utc_ApplicationFW_app2ext_move_func_03(void);
static void utc_ApplicationFW_app2ext_move_func_04(void);
static void utc_ApplicationFW_app2ext_move_func_05(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{utc_ApplicationFW_app2ext_move_func_01, POSITIVE_TC_IDX},
	{utc_ApplicationFW_app2ext_move_func_02, POSITIVE_TC_IDX},
	{utc_ApplicationFW_app2ext_move_func_03, NEGATIVE_TC_IDX},
	{utc_ApplicationFW_app2ext_move_func_04, NEGATIVE_TC_IDX},
	{utc_ApplicationFW_app2ext_move_func_05, NEGATIVE_TC_IDX},
	{NULL, 0}
};

app2ext_handle *handle = NULL;

static void startup(void)
{
	int ret = -1;
	ret = system("pkgcmd -it rpm -p /mnt/nfs/TC-tet/unit/com.samsung.calculator-0.1.36-1.armv7l.rpm -q");
        if (ret != 0) {
                tet_infoline("Unable to install");
                tet_result(TET_UNINITIATED);
                return;
        }
        handle = app2ext_init(APP2EXT_SD_CARD);
        if (handle == NULL) {
                tet_infoline("Unable to call app2ext_init()");
                tet_result(TET_UNINITIATED);
                return;
        }
}

static void cleanup(void)
{
	if (handle) {
		app2ext_deinit(handle);
	}
}

static GList * populate_dir_details()
{
	GList *dir_list = NULL;
	GList *list = NULL;
	app2ext_dir_details* dir_detail = NULL;
	int i;


	for (i=0; i<3; i++) {
		dir_detail = (app2ext_dir_details*) calloc(1, sizeof(app2ext_dir_details));
		if (dir_detail == NULL) {
			printf("\nMemory allocation failed\n");
			goto FINISH_OFF;
		}
		dir_detail->name = (char*) calloc(1, sizeof(char)*(strlen(pkg_ro_content_rpm[i])+2));
		if (dir_detail->name == NULL) {
			printf("\nMemory allocation failed\n");
			free(dir_detail);
			goto FINISH_OFF;
		}
		snprintf(dir_detail->name, (strlen(pkg_ro_content_rpm[i])+1), "%s", pkg_ro_content_rpm[i]);
		dir_detail->type = APP2EXT_DIR_RO;
		dir_list = g_list_append(dir_list, dir_detail);
	}
	if (dir_list) {
		list = g_list_first(dir_list);
		while (list) {
			dir_detail = (app2ext_dir_details *)list->data;
			list = g_list_next(list);
		}
	}
	return dir_list;
FINISH_OFF:
	if (dir_list) {
		list = g_list_first(dir_list);
		while (list) {
			dir_detail = (app2ext_dir_details *)list->data;
			if (dir_detail && dir_detail->name) {
				free(dir_detail->name);
			}
			list = g_list_next(list);
		}
		g_list_free(dir_list);
	}
	return NULL;
}

static void clear_dir_list(GList* dir_list)
{
	GList *list = NULL;
	app2ext_dir_details* dir_detail = NULL;
	if (dir_list) {
		list = g_list_first(dir_list);
		while (list) {
			dir_detail = (app2ext_dir_details *)list->data;
			if (dir_detail && dir_detail->name) {
				free(dir_detail->name);
			}
			list = g_list_next(list);
		}
		g_list_free(dir_list);
	}
}

/**
 * @brief Positive test case of app2ext_move()
 */
static void utc_ApplicationFW_app2ext_move_func_01(void)
{
	int ret = APP2EXT_SUCCESS;
	GList *dir_list = populate_dir_details();
	if (dir_list == NULL) {
		printf("\nError in populating the directory list\n");
		return -1;
	}

	ret = handle->interface.move("com.samsung.calculator", dir_list, APP2EXT_MOVE_TO_PHONE);
	if (ret != APP2EXT_SUCCESS) {
		tet_infoline
		    ("app2ext_move() failed in positive test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}
/**
 * @brief Positive test case of app2ext_move()
 */
static void utc_ApplicationFW_app2ext_move_func_02(void)
{
	int ret = APP2EXT_SUCCESS;
	GList *dir_list = populate_dir_details();
	if (dir_list == NULL) {
		printf("\nError in populating the directory list\n");
		return -1;
	}

	ret = handle->interface.move("com.samsung.calculator", dir_list, APP2EXT_MOVE_TO_EXT);
	if (ret != APP2EXT_SUCCESS) {
		tet_infoline
		    ("app2ext_move() failed in positive test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of app2ext_move()
 */
static void utc_ApplicationFW_app2ext_move_func_03(void)
{
	int ret = APP2EXT_SUCCESS;
	GList *dir_list = populate_dir_details();
	if (dir_list == NULL) {
		printf("\nError in populating the directory list\n");
		return -1;
	}

	ret = handle->interface.move(NULL, dir_list, APP2EXT_MOVE_TO_PHONE);
	if (ret == APP2EXT_SUCCESS) {
		tet_infoline
		    ("app2ext_move() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of app2ext_move()
 */
static void utc_ApplicationFW_app2ext_move_func_04(void)
{
	int ret = APP2EXT_SUCCESS;
	ret = handle->interface.move("com.samsung.calculator", NULL, APP2EXT_MOVE_TO_PHONE);
	if (ret == APP2EXT_SUCCESS) {
		tet_infoline
		    ("app2ext_move() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}
/**
 * @brief Negative test case of app2ext_move()
 */
static void utc_ApplicationFW_app2ext_move_func_05(void)
{
	int ret = APP2EXT_SUCCESS;
	GList *dir_list = populate_dir_details();
	if (dir_list == NULL) {
		printf("\nError in populating the directory list\n");
		return -1;
	}

	ret = handle->interface.move("com.samsung.calculator", dir_list, 10);
	if (ret == APP2EXT_SUCCESS) {
		tet_infoline
		    ("app2ext_move() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}
