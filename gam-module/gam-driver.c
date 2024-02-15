#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

/* Do a dmesg --follow to see messages being printed to the
 * kernel buffer.
 *
 * Do a cat /proc/gammodule to read a special message printed
 * by this module.
 */

// Module metadata
MODULE_AUTHOR("Gordon A MacDonald");
MODULE_DESCRIPTION("GAM kernel module");
MODULE_LICENSE("GPL");

static struct proc_dir_entry* proc_entry;

static ssize_t custom_read(struct file* file, char __user* user_buffer,
		size_t count, loff_t* offset)
{
	int ctu = 0;

	// This will print a message to the kernel buffer upon read.
	printk(KERN_INFO "Calling the custom read method.");

	char greeting[] = "GAM in da house!\n";
	int greeting_length = strlen(greeting);

	if (*offset > 0)
		return 0;

	// Prints message in user-space when /proc/gammodule is read.
	ctu = copy_to_user(user_buffer, greeting, greeting_length);
	*offset = greeting_length;

	return greeting_length;
}

static struct proc_ops pops =
{
	.proc_read = custom_read,
};

// Custom init and exit methods
static int __init custom_init(void) {
	proc_entry = proc_create("gammodule", 0666, NULL, &pops);
	// Prints a message to the kernel buffer upon load. 
	printk(KERN_INFO "GAM module loaded.");
	return 0;
}

static void __exit custom_exit(void) {
	proc_remove(proc_entry);
	// Prints a message to the kernel buffer upon unload.
	printk(KERN_INFO "GAM module unloaded.");
}

module_init(custom_init);
module_exit(custom_exit);

