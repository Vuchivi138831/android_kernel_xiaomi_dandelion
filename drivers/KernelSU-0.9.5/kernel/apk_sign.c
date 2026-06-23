#include <linux/err.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/version.h>
#ifdef CONFIG_KSU_DEBUG
#include <linux/moduleparam.h>
#endif

#include "apk_sign.h"
#include "klog.h" // IWYU pragma: keep
#include "kernel_compat.h"

#ifdef CONFIG_KSU_DEBUG

int ksu_debug_manager_uid = -1;

#include "manager.h"

static int set_expected_size(const char *val, const struct kernel_param *kp)
{
	int rv = param_set_uint(val, kp);
	ksu_set_manager_uid(ksu_debug_manager_uid);
	pr_info("ksu_manager_uid set to %d\n", ksu_debug_manager_uid);
	return rv;
}

static struct kernel_param_ops expected_size_ops = {
	.set = set_expected_size,
	.get = param_get_uint,
};

module_param_cb(ksu_debug_manager_uid, &expected_size_ops,
		&ksu_debug_manager_uid, S_IRUSR | S_IWUSR);

#endif

/**
 * Hàm kiểm tra tính hợp lệ của ứng dụng quản lý.
 * Trong cấu hình thử nghiệm này, hàm luôn trả về true để chấp nhận mọi APK.
 */
bool is_manager_apk(char *path)
{
	// Phục vụ mục đích thử nghiệm: Bỏ qua kiểm tra chữ ký và chấp nhận mọi đường dẫn
	return true;
}
