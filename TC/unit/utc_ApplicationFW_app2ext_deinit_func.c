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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
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

static void utc_ApplicationFW_app2ext_deinit_func_01(void);
static void utc_ApplicationFW_app2ext_deinit_func_02(void);
static void utc_ApplicationFW_app2ext_deinit_func_03(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{utc_ApplicationFW_app2ext_deinit_func_01, POSITIVE_TC_IDX},
	{utc_ApplicationFW_app2ext_deinit_func_02, NEGATIVE_TC_IDX},
	{utc_ApplicationFW_app2ext_deinit_func_03, NEGATIVE_TC_IDX},
	{NULL, 0}
};

app2ext_handle *handle1 = NULL;
app2ext_handle *handle2 = NULL;


static void startup(void)
{
        handle1 = app2ext_init(APP2EXT_SD_CARD);
        if (handle1 == NULL) {
                tet_infoline("Unable to call app2ext_init()");
                tet_result(TET_UNINITIATED);
                return;
        }
        handle2 = app2ext_init(APP2EXT_SD_CARD);
        if (handle2 == NULL) {
                tet_infoline("Unable to call app2ext_init()");
                tet_result(TET_UNINITIATED);
                return;
        }
}

static void cleanup(void)
{
}

/**
 * @brief Positive test case of app2ext_deinit()
 */
static void utc_ApplicationFW_app2ext_deinit_func_01(void)
{
	int ret = app2ext_deinit(handle1);

	if (ret != 0) {
		tet_infoline
		    ("app2ext_deinit() failed in positive test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of app2ext_deinit()
 */
static void utc_ApplicationFW_app2ext_deinit_func_02(void)
{
	int ret = app2ext_deinit(NULL);

	if (ret == 0) {
		tet_infoline
		    ("app2ext_deinit() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of app2ext_deinit()
 */
static void utc_ApplicationFW_app2ext_deinit_func_03(void)
{
	int ret = app2ext_deinit(handle2);

	if (ret != 0) {
		tet_infoline
		    ("app2ext_deinit() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}
	handle2= NULL;
	ret = app2ext_deinit(handle2);

	if (ret == 0) {
		tet_infoline
		    ("app2ext_deinit() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}

	tet_result(TET_PASS);
}
