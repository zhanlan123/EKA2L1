/*
 * Copyright (c) 2019 EKA2L1 Team
 * 
 * This file is part of EKA2L1 project.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <epoc/services/hwrm/light/light.h>
#include <epoc/services/hwrm/op.h>
#include <epoc/services/context.h>

#include <common/e32inc.h>
#include <e32err.h>

namespace eka2l1::epoc {
    const char *light_op_to_string(const int op) {
        switch (op) {
        case hwrm_light_op_on:
            return "Light on";

        case hwrm_light_op_off:
            return "Light off";

        case hwrm_light_op_blink:
            return "Light blink";

        case hwrm_light_op_cleanup_lights:
            return "Clean lights service";

        case hwrm_light_op_reserve_lights:
            return "Reserve lights";

        case hwrm_light_op_release_lights: 
            return "Release lights";

        case hwrm_light_op_set_light_color:
            return "Set light color";

        case hwrm_light_op_supported_targets:
            return "Get supported targets";

        default:
            break;
        }

        return "Unknown ?";
    }

    void light_resource::get_supported_targets(service::ipc_context &ctx) {
        LOG_TRACE("Light resource's get supported targets stubbed with -1 (all permitted)");
        std::uint32_t support_mask = static_cast<std::uint32_t>(-1);

        ctx.write_arg_pkg(0, support_mask);
        ctx.set_request_status(KErrNone);
    }

    void light_resource::execute_command(service::ipc_context &ctx) {
        switch (ctx.msg->function) {
        case hwrm_light_op_supported_targets: {
            get_supported_targets(ctx);
            break;
        }

        default:
            LOG_ERROR("Unimplemented operation for light resource: {} ({})", light_op_to_string(ctx.msg->function),
                ctx.msg->function);
            break;
        }
    }
}