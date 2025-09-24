package org.love2d.android.ui

import org.love2d.android.adapter.BaseBindingQuickAdapter
import org.love2d.android.executable.databinding.ModItemLayoutBinding

/**
 * ClassName ModAdapter
 * Description
 * Create by hjr
 * Date 2025/6/17 15:21
 */
class ModAdapter : BaseBindingQuickAdapter<String, ModItemLayoutBinding>(
    ModItemLayoutBinding::inflate
) {

    private lateinit var onDelete : (String) -> Unit
    fun setOnDeleteListener(listener: (String) -> Unit) {
        onDelete = listener
    }

    override fun viewBindingConvert(holder: BaseBindingHolder, binding: ModItemLayoutBinding, item: String) {
        binding.modName.text = item

        binding.deleteBtn.setOnClickListener {
            if (::onDelete.isInitialized) {
                onDelete(item)
            }
        }
    }
}