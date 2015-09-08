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

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;

static void utc_ApplicationFW_app2ext_post_uninstall_func_01(void);
static void utc_ApplicationFW_app2ext_post_uninstall_func_02(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{utc_ApplicationFW_app2ext_post_uninstall_func_01, POSITIVE_TC_IDX},
	{utc_ApplicationFW_app2ext_post_uninstall_func_02, NEGATIVE_TC_IDX},
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
	ret = handle->interface.pre_uninstall("com.samsung.calculator");
	if (ret) {
		tet_infoline
		    ("Unable to do app2ext_pre_uninstall()");
		tet_result(TET_UNINITIATED);
		handle->interface.post_uninstall("com.samsung.calculator");
		return;
	}
}

static void cleanup(void)
{
	app2ext_deinit(handle);
	int ret = -1;
	ret = system("pkgcmd -ut rpm -n com.samsung.calculator -q");
        if (ret != 0) {
                tet_infoline("Unable to uninstall");
                tet_result(TET_UNINITIATED);
                return;
        }
}

/**
 * @brief Positive test case of app2ext_post_uninstall()
 */
static void utc_ApplicationFW_app2ext_post_uninstall_func_01(void)
{
	int ret = APP2EXT_SUCCESS;

	ret = handle->interface.post_uninstall("com.samsung.calculator");
	if (ret != APP2EXT_SUCCESS) {
		tet_infoline
		    ("app2ext_post_uninstall() failed in positive test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of app2ext_post_uninstall()
 */
static void utc_ApplicationFW_app2ext_post_uninstall_func_02(void)
{
	int ret = APP2EXT_SUCCESS;
	ret = handle->interface.post_uninstall(NULL);
	if (ret == APP2EXT_SUCCESS) {
		tet_infoline
		    ("app2ext_post_uninstall() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}
