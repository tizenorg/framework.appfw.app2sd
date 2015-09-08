/*
 *  app2ext
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

static void utc_ApplicationFW_app2ext_init_func_01(void);
static void utc_ApplicationFW_app2ext_init_func_02(void);
static void utc_ApplicationFW_app2ext_init_func_03(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX = 0x02,
};

struct tet_testlist tet_testlist[] = {
	{utc_ApplicationFW_app2ext_init_func_01, POSITIVE_TC_IDX},
	{utc_ApplicationFW_app2ext_init_func_02, POSITIVE_TC_IDX},
	{utc_ApplicationFW_app2ext_init_func_03, NEGATIVE_TC_IDX},
	{NULL, 0}
};

int r = APP2EXT_SUCCESS;

static void startup(void)
{
}

static void cleanup(void)
{
}

/**
 * @brief Positive test case of app2ext_init()
 */
static void utc_ApplicationFW_app2ext_init_func_01(void)
{
	app2ext_handle *handle = NULL;
        handle = app2ext_init(APP2EXT_SD_CARD);
        if (handle == NULL) {
                tet_infoline("app2ext_init() failed in positive test case");
		tet_result(TET_FAIL);
                return;
        }
	tet_result(TET_PASS);
}

/**
 * @brief Positive test case of app2ext_init()
 */
static void utc_ApplicationFW_app2ext_init_func_02(void)
{
	app2ext_handle *handle1 = NULL;
	app2ext_handle *handle2 = NULL;
        handle1 = app2ext_init(APP2EXT_SD_CARD);
        if (handle1 == NULL) {
                tet_infoline("app2ext_init() failed in positive test case");
		tet_result(TET_FAIL);
                return;
        }
        handle2 = app2ext_init(APP2EXT_SD_CARD);
        if (handle2 == NULL) {
                tet_infoline("app2ext_init() failed in positive test case");
		tet_result(TET_FAIL);
                return;
        }
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of app2ext_init()
 */
static void utc_ApplicationFW_app2ext_init_func_03(void)
{
	app2ext_handle *handle = NULL;
        handle = app2ext_init(10);
        if (handle != NULL) {
                tet_infoline("app2ext_init() failed in negative test case");
		tet_result(TET_FAIL);
                return;
        }
	tet_result(TET_PASS);
}

